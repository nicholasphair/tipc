#include "ASTHelper.h"

#include <catch2/catch.hpp>

#include <iostream>

TEST_CASE("ASTProgramTest: ASTProgram output is the hash of the source.", "[ASTProgram]") {
  std::stringstream stream;
  stream << R"(
      foo(x) {
         return x + 1;
      }

      main() {
        var z;
        z = foo(42);
        return z;
      }
    )";

  auto ast = ASTHelper::build_ast(stream);

  std::string expectedOutput = "2127836233143005711";
  std::stringstream actualOutput;
  actualOutput << *ast;
  REQUIRE(expectedOutput == actualOutput.str());
}

TEST_CASE("ASTProgramTest: ASTProgram returns nullptr when getting nonexistent function", "[ASTProgram]") {
  std::stringstream stream;
  stream << R"(
      foo(x) { return x; }
      bar(x) { return x; }
      baz(x) { return x; }
    )";

  auto ast = ASTHelper::build_ast(stream);
  ASTFunction * expectedFunction = nullptr;
  ASTFunction * actualFunction = ast->findFunctionByName("fred");
  REQUIRE(expectedFunction == actualFunction);
}
