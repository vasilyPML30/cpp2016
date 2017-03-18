#ifndef MY_ARRAY_BOOL_REAL_H_
#define MY_ARRAY_BOOL_REAL_H_

#include "my_array.h"

template<std::size_t N>
my_array<bool, N>::my_array() {
  std::memset(_data, 0, LEN_TO_SIZE(N));
}

template<std::size_t N>
void my_array<bool, N>::check_range(std::size_t index) const {
  if (index < 0 || N <= index)
    throw std::out_of_range("invalid index\n");  
}

template<std::size_t N>
std::size_t my_array<bool, N>::size() const {
  return N;
}

template<std::size_t N>
bool my_array<bool, N>::empty() const {
  return !size();
}

template<std::size_t N>
typename my_array<bool, N>::proxy my_array<bool, N>::at(std::size_t index) {
  check_range(index);
  return (*this)[index];
}

template<std::size_t N>
bool my_array<bool, N>::at(std::size_t index) const {
  check_range(index);
  return (*this)[index];
}

template<std::size_t N>
typename my_array<bool, N>::proxy
my_array<bool, N>::operator[](std::size_t index) {
  return proxy(_data, index);
}

template<std::size_t N>
bool my_array<bool, N>::operator[](std::size_t index) const {
  return _data[index / 8] & (1 << (index % 8));
}

template<std::size_t N>
void my_array<bool, N>::fill(bool val) {
  for (size_t i = 0; i < N; i++)
    at(i) = val;
}

template<std::size_t N>
my_array<bool, N>::proxy::proxy(char* begin, size_t index):
                                         _byte(begin[index / 8]) {
  _bit_pos = (index % 8);
}

template<std::size_t N>
typename my_array<bool, N>::proxy my_array<bool, N>::proxy::operator=(bool val) {
  if (val)
    _byte |= (1 << _bit_pos);
  else
    _byte &= ~(char)(1 << _bit_pos);
  return *this;
}

template<std::size_t N>
typename my_array<bool, N>::proxy
my_array<bool, N>::proxy::operator=(my_array<bool, N>::proxy val) {
  return *this = (bool)val;
}

template<std::size_t N>
my_array<bool, N>::proxy::operator bool() const {
  return _byte & (1 << _bit_pos);
}

#endif