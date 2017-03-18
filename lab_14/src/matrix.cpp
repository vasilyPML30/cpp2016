#include "matrix.h"
#include <cstring>

void Matrix::allocate() {
  if (!rows_ || !cols_)
    data_ = NULL;
  else {
    int32_t* tmp = new int32_t[rows_ * cols_]();
    data_ = new int32_t*[rows_];
    for (std::size_t i = 0; i < rows_; i++)
      data_[i] = tmp + i * cols_;
  }  
}  

Matrix::Matrix(std::size_t rows, std::size_t cols) {
  rows_ = rows;
  cols_ = cols;
  allocate();
}

Matrix::Matrix() {
  rows_ = cols_ = 0;
  data_ = NULL;
}

Matrix::Matrix(const Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  allocate();
  if (data_)
    memcpy(*data_, *(other.data_), rows_ * cols_ * sizeof(**data_));
}

Matrix::~Matrix() {
  if (data_) {
    delete [] *data_;
    delete [] data_;
  }
}

Matrix& Matrix::operator=(Matrix other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(data_, other.data_);
  return *this;
}

std::ostream& operator<<(std::ostream& file, const Matrix& matr) {
  if (matr.rows() && matr.cols())
    for (std::size_t i = 0; i < matr.rows(); i++) {
      for (std::size_t j = 0; j < matr.cols(); j++) {
        file << matr.element(i, j);
        if (j < matr.cols() - 1)
          file << " ";
      }
      file << std::endl;
    }
  return file;
}

std::istream& operator>>(std::istream& file, Matrix& matr) {
  size_t rows, cols;
  file >> rows >> cols;
  Matrix tmp(rows, cols);
  for (std::size_t i = 0; i < tmp.rows(); i++)
    for (std::size_t j = 0; j < tmp.cols(); j++)
      file >> tmp.element(i, j);
  matr = tmp;
  return file;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw MatrixException("ADD: dimensions do not match.");
  for (std::size_t i = 0; i < other.rows_; i++)
    for (std::size_t j = 0; j < other.cols_; j++)
      element(i, j) += other.element(i, j);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  if (cols_ != other.rows_)
    throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
  Matrix tmp(rows_, other.cols_);
  for (std::size_t i = 0; i < rows_; i++)
    for (std::size_t j = 0; j < other.cols_; j++)
      for (std::size_t k = 0; k < cols_; k++)
        tmp.element(i, j) += element(i, k) * other.element(k, j);
  return *this = tmp;
}

int32_t& Matrix::element(int32_t row, int32_t col) const {
  if (row < 0 || (int32_t)rows_ <= row ||
      col < 0 || (int32_t)cols_ <= col)
    throw MatrixException("ACCESS: bad index.");
  return data_[row][col];
}

std::size_t Matrix::cols() const {
  return cols_;
}
std::size_t Matrix::rows() const {
  return rows_;
}

MatrixException::MatrixException(const char* s) : logic_error(s) { }
