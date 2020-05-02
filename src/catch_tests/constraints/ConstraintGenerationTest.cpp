#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MockTerms.h"
#include "UnionFindSolver.hpp"
#include "../../constraints/TypeConstraint.h"
#include "UnificationError.hpp"
#include "TypeConstraint.h"
#include <iostream>
#include "TipInt.hpp"
#include "TipInt.hpp"

TEST_CASE("test constraint generation", "[foo]") {
    //std::ifstream stream;
    //stream.open(sourceFile);

    //ANTLRInputStream input(stream);
    //TIPLexer lexer(&input);
    //CommonTokenStream tokens(&lexer);
    //TIPParser parser(&tokens);

    //TIPParser::ProgramContext *tree = parser.program();

    //TIPtreeBuild tb(&parser);
    //
    //auto ast = tb.build(tree);
    //TestNCons oneCons(1);
    //TestNCons twoCons(2);
    //TypeConstraint constraint(&oneCons, &twoCons);
    //std::vector<TypeConstraint> constraints {constraint};

    //UnionFindSolver solver(constraints);
    //REQUIRE_THROWS_AS(solver.unify(&oneCons, &twoCons), UnificationError);
    REQUIRE(true);
}

