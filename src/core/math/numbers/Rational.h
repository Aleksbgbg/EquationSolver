#ifndef SRC_CORE_MATH_NUMBERS_RATIONAL_H_
#define SRC_CORE_MATH_NUMBERS_RATIONAL_H_

#include <cmath>
#include <ostream>

#include "core/types.h"

class Rational {
 public:
  Rational();

  template <typename T>  // Assuming integers
  Rational(T value)
      : positive_(value >= static_cast<T>(0)),
        numerator_(std::abs(value)),
        denominator_(1) {}

  Rational(intmax numerator, size denominator);
  Rational(bool positive, size numerator, size denominator);

  template <typename T>
  explicit operator T() const {
    return static_cast<T>((SignAsNumber() * numerator_) / denominator_);
  }

  bool operator==(Rational other) const;

  Rational operator-() const;
  Rational operator+(Rational other) const;
  Rational operator-(Rational other) const;
  Rational operator*(Rational other) const;
  Rational operator/(Rational other) const;

  void operator+=(Rational other);
  void operator-=(Rational other);
  void operator*=(Rational other);
  void operator/=(Rational other);

  friend std::ostream& operator<<(std::ostream& stream, Rational number);

 private:
  bool IsZero() const;
  bool IsWhole() const;
  intmax SignAsNumber() const;
  Rational FlipSign() const;
  Rational FlipFraction() const;
  void Reduce();

  bool positive_;
  size numerator_;
  size denominator_;
};

#endif  // SRC_CORE_MATH_NUMBERS_RATIONAL_H_
