#include "task3/Calculate.hpp"
#include <catch2/catch_test_macros.hpp>

// Test class implementing the required interface
class TestNumber {
  int value;

public:
  TestNumber(int v) : value(v) {}
  static TestNumber identity() { return TestNumber(1); }
  int getValue() const { return value; }
  bool operator==(const TestNumber &other) const {
    return value == other.getValue();
  }
};

// Test binary operations
struct Multiply {
  TestNumber operator()(const TestNumber &a, const TestNumber &b) const {
    return TestNumber(a.getValue() * b.getValue());
  }
};

struct Add {
  TestNumber operator()(const TestNumber &a, const TestNumber &b) const {
    return TestNumber(a.getValue() + b.getValue());
  }
};

TEST_CASE("Calculate basic functionality", "[task3]") {
  TestNumber value(2);
  Multiply mult;
  Add add;

  SECTION("Zero and negative n returns identity") {
    REQUIRE(calculate(0, value, mult) == TestNumber(1));
    REQUIRE(calculate(-1, value, mult) == TestNumber(1));
  }

  SECTION("n=1 returns value") { REQUIRE(calculate(1, value, mult) == value); }

  SECTION("Multiplication operation") {
    // 2^3 = 8
    REQUIRE(calculate(3, value, mult) == TestNumber(8));
    // 2^4 = 16
    REQUIRE(calculate(4, value, mult) == TestNumber(16));
  }

  SECTION("Addition operation") {
    // 2 + 2 + 2 = 6
    REQUIRE(calculate(3, value, add) == TestNumber(6));
    // 2 + 2 + 2 + 2 = 8
    REQUIRE(calculate(4, value, add) == TestNumber(8));
  }

  SECTION("Large n values") {
    // 2^8 = 256
    REQUIRE(calculate(8, value, mult) == TestNumber(256));
  }
}

TEST_CASE("Calculate properties", "[calculate]") {
  TestNumber value(3);
  Multiply mult;

  SECTION("Identity property") {
    // f(x, identity()) = x
    REQUIRE(calculate(1, value, mult) == value);
    // f(identity(), x) = x
    REQUIRE(mult(TestNumber::identity(), value) == value);
    REQUIRE(mult(value, TestNumber::identity()) == value);
  }

  SECTION("Associativity") {
    // Test f(f(x,x), x) = f(x, f(x,x))
    TestNumber x(2);
    TestNumber fx = mult(x, x);          // 2 * 2 = 4
    REQUIRE(mult(fx, x) == mult(x, fx)); // (2*2)*2 = 2*(2*2)
  }
}
