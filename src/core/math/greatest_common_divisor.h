#ifndef SRC_CORE_MATH_GREATEST_COMMON_DIVISOR_H_
#define SRC_CORE_MATH_GREATEST_COMMON_DIVISOR_H_

template <typename T>
T GreatestCommonDivisor(T a, T b) {
  if (a == static_cast<T>(0)) {
    return b;
  }

  if (b == static_cast<T>(0)) {
    return a;
  }

  if (a == b) {
    return a;
  }

  if (a > b) {
    return GreatestCommonDivisor(a - b, b);
  }

  return GreatestCommonDivisor(a, b - a);
}

#endif  // SRC_CORE_MATH_GREATEST_COMMON_DIVISOR_H_
