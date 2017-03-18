#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_

#include <cstddef>
#include <iostream>
#include <cstring>

template <class T>
class my_vector {
public:
  my_vector();
  my_vector(size_t n);
  my_vector(const my_vector& other);
  my_vector& operator=(my_vector other);
  ~my_vector();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  void resize(size_t n);
  void reserve(size_t n);
  const T& operator[](size_t index) const;
  T& operator[](size_t index);
  void push_back(const T& t);
  void pop_back();
  void clear();

private:
  void init(size_t sz, size_t cp);

  size_t capacity_;
  size_t size_;
  T* array_;
};

#include "my_vector_impl.h"

#endif