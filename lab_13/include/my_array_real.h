#ifndef MY_ARRAY_REAL_H_
#define MY_ARRAY_REAL_H_

#include "my_array.h"

template<typename T, std::size_t N>
T& my_array<T, N>::operator[](std::size_t index) {
  return _data[index];
}

template<typename T, std::size_t N>
const T& my_array<T, N>::operator[](std::size_t index) const {
  return _data[index];
}

template<typename T, std::size_t N>
void my_array<T, N>::check_range(std::size_t index) const {
  if (index < 0 || N <= index)
    throw std::out_of_range("invalid index\n");  
}

template<typename T, std::size_t N>
T& my_array<T, N>::at(std::size_t index) {
  check_range(index);
  return _data[index];
}

template<typename T, std::size_t N>
const T& my_array<T, N>::at(std::size_t index) const {
  check_range(index);
  return _data[index];
}

template<typename T, std::size_t N>
std::size_t my_array<T, N>::size() const {
  return N;
}

template<typename T, std::size_t N>
bool my_array<T, N>::empty() const {
  return !size();
}

template<typename T, std::size_t N>
void my_array<T, N>::fill(const T& val) {
  for (std::size_t i = 0; i < N; i++)
    _data[i] = val;
}

#endif