#include "task1/QueryEngine.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

TEST_CASE("QueryEngine basic add/ask", "[task1]") {
  QueryEngine engine;

  engine.add("When is New Year in China?");
  engine.add("When is New Year in Thailand?");
  engine.add("When are we going for a beer?");
  engine.add("Where is my phone?");

  SECTION("Full prefix match") {
    auto results = engine.ask("When is New Year");
    REQUIRE(results.size() == 2);
    REQUIRE_THAT(results,
                 Catch::Matchers::Contains("When is New Year in China?"));
    REQUIRE_THAT(results,
                 Catch::Matchers::Contains("When is New Year in Thailand?"));
  }

  SECTION("Single match") {
    auto results = engine.ask("Where");
    REQUIRE(results.size() == 1);
    REQUIRE(results[0] == "Where is my phone?");
  }

  SECTION("No match") {
    auto results = engine.ask("What is this place?");
    REQUIRE(results.empty());
  }

  SECTION("Partial match with overlap") {
    auto results = engine.ask("When");
    REQUIRE(results.size() == 3);
  }
}
