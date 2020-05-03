#include <iostream>
#include <stdlib.h>

#include "TIPLexer.h"
#include "TIPParser.h"
#include "TIPtreeBuild.h"
#include "TIPtreeGen.h"
#include "antlr4-runtime.h"
#include "llvm/Support/CommandLine.h"
#include "UnionFindSolver.hpp"
#include "TIPtreeTypeConstraintVisitor.h"
#include "UniqueIdentifiersVisitor.hpp"
#include "DeclarationsVisitor.hpp"

#include <set>
#include <UnificationError.hpp>

using namespace std;
using namespace antlr4;
using namespace TIPtree;
using namespace llvm;

static cl::OptionCategory
        TIPcat("tipc Options",
               "Options for controlling the TIP compilation process.");
static cl::opt<bool> pp("p", cl::desc("pretty print"), cl::cat(TIPcat));
static cl::opt<bool> ppWlines("l", cl::desc("pretty print with line numbers"),
                              cl::cat(TIPcat));
static cl::opt<bool> noOpt("d", cl::desc("disable bitcode optimization"),
                           cl::cat(TIPcat));
static cl::opt<bool> typeCheckEnabled("t", cl::desc("type check the input"),
                              cl::cat(TIPcat));
static cl::opt<std::string> sourceFile(cl::Positional,
                                       cl::desc("<tip source file>"),
                                       cl::Required, cl::cat(TIPcat));

int main(int argc, const char *argv[]) {
    cl::HideUnrelatedOptions(TIPcat); // suppress non TIP options
    cl::ParseCommandLineOptions(argc, argv, "tipc - a TIP to llvm compiler\n");

    std::ifstream stream;
    stream.open(sourceFile);

    ANTLRInputStream input(stream);
    TIPLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    TIPParser parser(&tokens);

    TIPParser::ProgramContext *tree = parser.program();

    TIPtreeBuild tb(&parser);
    auto ast = tb.build(tree);

    if(typeCheckEnabled) {
        // Make sure all identifiers are unique.
        UniqueIdentifiersVisitor uniqueIdentifiersVisitor;
        ast->accept(&uniqueIdentifiersVisitor);
        if(!uniqueIdentifiersVisitor.all_identifiers_unique()) {
            std::cerr << "ERROR: the following identifiers conflict with a previously observed identifier:\n" ;
            for(auto dup : uniqueIdentifiersVisitor.get_conflicting_identifiers()) {
                std::cerr << dup.first << " at line " << dup.second << "\n";
            }
            std::cerr << "tip assumes that no identifier in a program is declared more than once" << std::endl;
            exit(1);
        }

        // Run Declarations Analysis.
        DeclarationsVisitor declarationsVisitor;
        ast->accept(&declarationsVisitor);

        // Run Type Checking.
        TIPtreeTypeConstraintVisitor visitor(declarationsVisitor.get_canonicals());
        ast->accept(&visitor);
        UnionFindSolver solver(visitor.get_constraints());
        try {
            solver.solve();
        } catch(const UnificationError &e) {
            std::cerr << "ERROR: the input program has been found to be untypable." << std::endl;
            exit(1);
        }
    }

    if (pp || ppWlines) {
        std::cout << ast->print("  ", ppWlines);
    } else {
        auto theModule = ast->codegen(sourceFile);

        if (!noOpt) {
            // Create a pass manager to simplify generated module
            auto TheFPM =
                    llvm::make_unique<legacy::FunctionPassManager>(theModule.get());

            // Promote allocas to registers.
            TheFPM->add(createPromoteMemoryToRegisterPass());
            // Do simple "peephole" optimizations
            TheFPM->add(createInstructionCombiningPass());
            // Reassociate expressions.
            TheFPM->add(createReassociatePass());
            // Eliminate Common SubExpressions.
            TheFPM->add(createGVNPass());
            // Simplify the control flow graph (deleting unreachable blocks, etc).
            TheFPM->add(createCFGSimplificationPass());
            TheFPM->doInitialization();

            // run simplification pass on each function
            for (auto &fun : theModule->getFunctionList()) {
                TheFPM->run(fun);
            }
        }

        std::error_code ec;
        ToolOutputFile result(sourceFile + ".bc", ec, sys::fs::F_None);
        WriteBitcodeToFile(*theModule, result.os());
        result.keep();
    }
}
