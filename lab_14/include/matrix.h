#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <stdint.h>
#include <iostream>
#include <stdexcept>

class Matrix {
public:
  Matrix();
  Matrix(std::size_t rows, std::size_t cols);
  Matrix(const Matrix& other);
  ~Matrix();

  Matrix& operator=(Matrix other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  int32_t& element(int32_t row, int32_t col) const;
  std::size_t cols() const;
  std::size_t rows() const;


private:
  void allocate();
  std::size_t rows_, cols_;
  int32_t** data_;
};

class MatrixException : public std::logic_error {
public:
  MatrixException(const char* s);
};

std::ostream& operator<<(std::ostream& file, const Matrix& matr);
std::istream& operator>>(std::istream& file, Matrix& matr);

#endif