#include "Calculate.hpp"
#include <iostream>

// Example class that satisfies the IsSupported concept
class NumberWrapper {
  int value;

public:
  NumberWrapper(int v) : value(v) {}

  static NumberWrapper identity() { return NumberWrapper(1); }
  int getValue() const { return value; }

  friend std::ostream &operator<<(std::ostream &os, const NumberWrapper &nw) {
    return os << nw.value;
  }
};

// Example binary operation
struct Multiply {
  NumberWrapper operator()(const NumberWrapper &a,
                           const NumberWrapper &b) const {
    return NumberWrapper(a.getValue() * b.getValue());
  }
};

int main() {
  NumberWrapper x(2);
  Multiply mult;

  // Should compute 2^3 = 8
  auto result = calculate(3, x, mult);
  std::cout << "2^3 = " << result << std::endl;

  // Should compute 2^4 = 16
  result = calculate(4, x, mult);
  std::cout << "2^4 = " << result << std::endl;

  return 0;
}