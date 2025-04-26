#ifndef TASK3_CALCULATE_HPP
#define TASK3_CALCULATE_HPP

#include <concepts>

template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation) {
  { operation(first, second) } -> std::convertible_to<T>;
  { T::identity() } -> std::convertible_to<T>;
};

template <class BinaryOp, class ValueType>
  requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp &f) {
  if (n <= 0)
    return ValueType::identity();
  if (n == 1)
    return value;

  // For even n, we can use the associative property: f(f(x,x), f(x,x))
  if (n % 2 == 0) {
    ValueType half = calculate(n / 2, value, f);
    return f(half, half);
  }

  // For odd n, we calculate n-1 and then apply f one more time
  return f(calculate(n - 1, value, f), value);
}

#endif // TASK3_CALCULATE_HPP
