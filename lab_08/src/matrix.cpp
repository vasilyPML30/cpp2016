#include "matrix.h"
#include <algorithm>

int **Matrix::new_data(std::size_t r, std::size_t c) {
  int *tmp = new int[r * c];
  std::fill(tmp, tmp + r * c, 0);
  int **data = new int *[r];
  for (std::size_t i = 0; i < r; i++)
    data[i] = tmp + i * c;
  
  
  return data;
}

void Matrix::delete_data()
{
  delete [] _data[0];
  delete [] _data;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = new_data(r, c);
}

Matrix::~Matrix() {
  delete_data();
}

Matrix::Matrix(const Matrix& m){
  _rows = m._rows;
  _cols = m._cols;
  _data = new_data(_rows, _cols);
  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      _data[i][j] = m._data[i][j];
}

Matrix& Matrix::operator=(const Matrix& m){
  if (this != &m) {
    Matrix tmp = m;
    std::swap(_rows, tmp._rows);
    std::swap(_cols, tmp._cols);
    std::swap(_data, tmp._data);
  }
  return *this;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for (std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < _cols; j++)
      fprintf(f, "%i ", _data[i][j]);
    fprintf(f, "\n");
  }
}

bool Matrix::operator==(const Matrix& m) const {
  if (_cols != m._cols || _rows != m._rows)
    return false;
  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      if (_data[i][j] != m._data[i][j])
        return false;
  return true;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !operator==(m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      _data[i][j] += m._data[i][j];
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  *this = *this - m;
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  *this = *this * m;
  return *this;
}

Matrix& Matrix::operator*=(int x) {
  *this = *this * x;
  return *this;
}

const Matrix Matrix::operator+(const Matrix& m) const {
  Matrix tmp(*this);
  return tmp += m;
}

Matrix Matrix::operator*(int x) const {
  Matrix tmp(_rows, _cols);
  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < _cols; j++)
      tmp._data[i][j] = _data[i][j] * x;
  return tmp;
}

Matrix Matrix::operator-(const Matrix& m) const {
  return *this + m * -1;
}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix tmp(_rows, m._cols);
  for (std::size_t i = 0; i < _rows; i++)
    for (std::size_t j = 0; j < m._cols; j++)
      for (std::size_t k = 0; k < _cols; k++)
        tmp._data[i][j] += _data[i][k] * m._data[k][j];
  return tmp;
}
