#include "Rational.h"

#include "core/math/greatest_common_divisor.h"

Rational::Rational() : positive_(true), numerator_(0), denominator_(1) {}

Rational::Rational(intmax numerator, size denominator)
    : Rational(numerator >= 0, std::abs(numerator), denominator) {}

Rational::Rational(bool positive, size numerator, size denominator)
    : positive_((numerator == 0) || positive),
      numerator_(numerator),
      denominator_(denominator) {
  Reduce();
}

bool Rational::operator==(Rational other) const {
  return (positive_ == other.positive_) && (numerator_ == other.numerator_) &&
         (denominator_ == other.denominator_);
}

Rational Rational::operator-() const {
  return this->FlipSign();
}

Rational Rational::operator+(Rational other) const {
  intmax newNumerator =
      (SignAsNumber() * numerator_ * other.denominator_) +
      (other.SignAsNumber() * other.numerator_ * denominator_);
  size newDenominator = denominator_ * other.denominator_;
  return Rational(newNumerator, newDenominator);
}

Rational Rational::operator-(Rational other) const {
  return (*this) + (-other);
}

Rational Rational::operator*(Rational other) const {
  intmax newNumerator =
      SignAsNumber() * numerator_ * other.SignAsNumber() * other.numerator_;
  size newDenominator = denominator_ * other.denominator_;
  return Rational(newNumerator, newDenominator);
}

Rational Rational::operator/(Rational other) const {
  return (*this) * other.FlipFraction();
}

void Rational::operator+=(Rational other) {
  new (this) Rational((*this) + other);
}

void Rational::operator-=(Rational other) {
  new (this) Rational((*this) - other);
}

void Rational::operator*=(Rational other) {
  new (this) Rational((*this) * other);
}

void Rational::operator/=(Rational other) {
  new (this) Rational((*this) / other);
}

bool Rational::IsZero() const {
  return numerator_ == 0;
}

bool Rational::IsWhole() const {
  return denominator_ == 1;
}

intmax Rational::SignAsNumber() const {
  return positive_ ? 1 : -1;
}

Rational Rational::FlipSign() const {
  if (IsZero()) {
    return *this;
  }

  Rational value = *this;
  value.positive_ = !positive_;
  return value;
}

Rational Rational::FlipFraction() const {
  Rational value = *this;
  std::swap(value.numerator_, value.denominator_);
  return value;
}

void Rational::Reduce() {
  size divisor = GreatestCommonDivisor(numerator_, denominator_);
  numerator_ /= divisor;
  denominator_ /= divisor;
}

std::ostream& operator<<(std::ostream& stream, Rational number) {
  if (!number.positive_) {
    stream << '-';
  }

  stream << number.numerator_;

  if (!number.IsWhole()) {
    stream << " / " << number.denominator_;
  }

  return stream;
}
