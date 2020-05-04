#include "catch.hpp"
#include <sstream>
#include "ASTHelper.hpp"
#include "DeclarationsVisitor.hpp"

TEST_CASE("test each identifier is represented", "[DeclarationsVisitor]") {
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
    DeclarationsVisitor visitor;
    ast->accept(&visitor);
    auto canonicals = visitor.get_canonicals();

    REQUIRE(canonicals.size() == 5);
    REQUIRE(canonicals.count("x") != 0);
    REQUIRE(canonicals.count("y") != 0);
    REQUIRE(canonicals.count("main") != 0);
    REQUIRE(canonicals.count("foo") != 0);
}

TEST_CASE("test each identifier is represented 2", "[DeclarationsVisitor]") {
    std::stringstream stream;
    stream << R"(
        foo(a) {
         var x, y, z ;
         x = input;
         y = null;
         y = &x;
         z = alloc y;
         return y;
        }
    )";

    auto ast = ASTHelper::build_ast(stream);
    DeclarationsVisitor visitor;
    ast->accept(&visitor);
    auto canonicals = visitor.get_canonicals();

    REQUIRE(canonicals.size() == 9);
    REQUIRE(canonicals.count("foo") != 0);
    REQUIRE(canonicals.count("a") != 0);
    REQUIRE(canonicals.count("x") != 0);
    REQUIRE(canonicals.count("input") != 0);
    REQUIRE(canonicals.count("y") != 0);
    REQUIRE(canonicals.count("null") != 0);
    REQUIRE(canonicals.count("&x") != 0);
    REQUIRE(canonicals.count("z") != 0);
    REQUIRE(canonicals.count("alloc y") != 0);
}
