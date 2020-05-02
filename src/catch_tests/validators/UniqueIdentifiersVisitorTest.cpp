#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream>
#include "ASTHelper.hpp"
#include "UniqueIdentifiersVisitor.hpp"

TEST_CASE("test identifying unique identifiers", "[UniqueIdentifiersVisitor]") {
    std::stringstream stream;
    stream << R"(
        foo() {
         var y;
         y = 1;
         return y;
        }

        main() {
          var x;
          return x;
        }
    )";

    auto ast = ASTHelper::build_ast(stream);
    UniqueIdentifiersVisitor visitor;
    ast->accept(&visitor);
    REQUIRE(visitor.all_identifiers_unique());
}


TEST_CASE("test identifying conflicting identifiers", "[UniqueIdentifiersVisitor]") {
    std::stringstream stream;
    stream << R"(
        bar() {
         var y;
         y = 1;
         return y;
        }

        foo(y) {
         var y;
         y = 1;
         return y;
        }

        main() {
          var y;
          return y;
        }
    )";

    auto ast = ASTHelper::build_ast(stream);
    UniqueIdentifiersVisitor visitor;
    ast->accept(&visitor);
    REQUIRE_FALSE(visitor.all_identifiers_unique());
    REQUIRE(visitor.get_conflicting_identifiers().size() == 3);
}

TEST_CASE("test only declarations are analyzed", "[UniqueIdentifiersVisitor]") {
    std::stringstream stream;
    stream << R"(
        foo(y) {
         y = 1;
         return y;
        }
    )";

    auto ast = ASTHelper::build_ast(stream);
    UniqueIdentifiersVisitor visitor;
    ast->accept(&visitor);
    REQUIRE(visitor.all_identifiers_unique());
}
