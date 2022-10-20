#ifndef SRC_CORE_MATH_MATRIX_H_
#define SRC_CORE_MATH_MATRIX_H_

#include <ostream>
#include <utility>
#include <vector>

#include "core/types.h"
#include "numbers/Rational.h"

template <typename Number>
class Matrix {
 public:
  Matrix(size rows, size cols) : rows_(rows), cols_(cols), entries_(rows_) {
    for (size row = 0; row < rows_; ++row) {
      entries_.at(row).resize(cols_);
    }
  }

  explicit Matrix(std::vector<std::vector<Number>> entries)
      : rows_(entries.size()),
        cols_(rows_ == 0 ? 0 : entries.at(0).size()),
        entries_(std::move(entries)) {}

  Number Get(size row, size col) const {
    return entries_.at(row).at(col);
  }

  void Set(size row, size col, Number value) {
    entries_.at(row).at(col) = value;
  }

  Matrix ReducedRowEchelonForm() const {
    Matrix copy = *this;
    copy.RowReduce();
    return copy;
  }

  bool operator==(Matrix other) const {
    bool equals = true;

    for (size row = 0; row < rows_; ++row) {
      for (size col = 0; col < cols_; ++col) {
        equals = equals && (Get(row, col) == other.Get(row, col));
      }
    }

    return equals;
  }

  friend std::ostream& operator<<(std::ostream& stream, Matrix m) {
    stream << "[\n";
    for (size row = 0; row < m.rows_; ++row) {
      stream << '\t';
      for (size col = 0; col < m.cols_; ++col) {
        stream << m.Get(row, col) << ", ";
      }
      stream << '\n';
    }
    stream << "]\n";

    return stream;
  }

 private:
  void RowReduce() {
    size nonZeroRows = 0;

    for (size col = 0; col < cols_; ++col) {
      if (nonZeroRows == rows_) {
        break;
      }

      bool allZero = true;
      bool foundOne = false;
      size oneRow = -1;

      for (size row = nonZeroRows; row < rows_; ++row) {
        allZero = allZero && (Get(row, col) == Number(0));

        if (Get(row, col) == Number(1)) {
          foundOne = true;
          oneRow = row;
          break;
        }
      }

      if (allZero) {
        continue;
      }

      if (foundOne) {
        Swap(oneRow, nonZeroRows);
      } else {
        MultiplyByConstant(nonZeroRows, Number(1) / Get(nonZeroRows, col));
      }

      for (size row = 0; row < rows_; ++row) {
        if (row == nonZeroRows) {
          continue;
        }

        if (Get(row, col) != Number(0)) {
          MultiplyRow1ByConstantAndAddToRow2(nonZeroRows, row, -Get(row, col));
        }
      }

      ++nonZeroRows;
    }
  }

  void Swap(size row1, size row2) {
    std::swap(entries_.at(row1), entries_.at(row2));
  }

  void MultiplyByConstant(size row, Number value) {
    for (auto& entry : entries_.at(row)) {
      entry *= value;
    }
  }

  void MultiplyRow1ByConstantAndAddToRow2(size row1, size row2, Number value) {
    auto row1Copy = entries_.at(row1);
    for (auto& entry : row1Copy) {
      entry *= value;
    }

    for (size col = 0; col < cols_; ++col) {
      Set(row2, col, Get(row2, col) + row1Copy.at(col));
    }
  }

  size rows_;
  size cols_;
  std::vector<std::vector<Number>> entries_;
};

using MatrixRational = Matrix<Rational>;
using MatrixReal32 = Matrix<float>;
using MatrixReal64 = Matrix<double>;
using MatrixReal128 = Matrix<long double>;
using MatrixDef = MatrixRational;

#endif  // SRC_CORE_MATH_MATRIX_H_
