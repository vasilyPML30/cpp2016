#ifndef _TESTS_H_
#define _TESTS_H_

#include <iostream>
#include <string>
#include <sstream>

#include "my_vector.h"

template <class T>
bool ctors_test() {
  my_vector<T> arr;
  if (arr.size() || arr.capacity() != 2)
    return false;
  my_vector<T> brr(0);
  if (brr.size() || brr.capacity() != 2)
    return false;
  my_vector<T> crr(4);
  if (crr.size() != 4 || crr.capacity() != 4)
    return false;
  return true;
}

template <class T>
bool copy_test(const T& a, const T& b) {
  my_vector<T> arr1;
  arr1.push_back(a);
  arr1.push_back(b);
  my_vector<T> arr2(arr1);
  my_vector<T> arr3;
  arr3 = arr1;
  if (arr1.size() != arr2.size() || arr1.capacity() != arr2.capacity() ||
      arr1.size() != arr3.size() || arr1.capacity() != arr3.capacity())
    return false;
  if (arr1[0] != arr2[0] || arr1[0] != arr3[0] ||
      arr1[1] != arr2[1] || arr1[1] != arr3[1])
    return false;
  return true;
}

template <class T>
bool size_test(const T& a) {
  my_vector<T> arr;
  if (arr.size())
    return false;
  arr.resize(100);
  if (arr.size() != 100)
    return false;
  arr.push_back(a);
  if (arr.size() != 101)
    return false;
  return true;
}

template <class T>
bool capacity_test(const T& a) {
  my_vector<T> arr;
  if (arr.capacity() != 2)
    return false;
  arr.resize(128);
  if (arr.capacity() != 128)
    return false;
  arr.push_back(a);
  if (arr.capacity() != 256)
    return false;
  return true;
}

template <class T>
bool empty_test() {
  my_vector<T> arr(100);
  if (arr.empty())
    return false;
  arr.resize(0);
  if (!arr.empty())
    return false;
  return true;
}

template <class T>
bool resize_test() {
  my_vector<T> arr;
  arr.resize(2);
  if (arr.size() != 2 && arr.capacity() != 2)
    return false;
  arr.resize(128);
  if (arr.size() != 128 && arr.capacity() != 128)
    return false;
  arr.resize(200);
  if (arr.size() != 200 && arr.capacity() != 256)
    return false;
  arr.resize(33);
  if (arr.size() != 33 && arr.capacity() != 256)
    return false;
  return true;
}

template <class T>
bool reserve_test() {
 my_vector<T> arr;
  arr.reserve(2);
  if (arr.capacity() != 2)
    return false;
  arr.reserve(128);
  if (arr.capacity() != 128)
    return false;
  arr.reserve(200);
  if (arr.capacity() != 256)
    return false;
  arr.reserve(33);
  if (arr.capacity() != 256)
    return false;
  return true; 
}

template <class T>
bool get_set_test(const T& a, const T& b) {
  my_vector<T> arr(2);
  arr[0] = T(a);
  arr[1] = T(b);
  T c = arr[0];
  T d = arr[1];
  if (a != arr[0] || a != c || b != arr[1] || b != d)
    return false;
  return true;
}

template <class T>
bool push_back_test(const T& a, const T& b) {
  my_vector<T> arr(7);
  arr.push_back(a);
  if (arr.size() != 8 || arr.capacity() != 8)
    return false;
  arr.push_back(b);
  if (arr.size() != 9 || arr.capacity() != 16)
    return false;
  if (arr[7] != a || arr[8] != b)
    return false;
  return true;
}

template <class T>
bool pop_back_test() {
  my_vector<T> arr(9);
  arr.pop_back();
  if (arr.size() != 8 || arr.capacity() != 16)
    return false;
  arr.pop_back();
  if (arr.size() != 7 || arr.capacity() != 16)
    return false;
  return true;
}

template <class T>
bool clear_test(const T& a) {
  my_vector<T> arr(7);
  arr.push_back(a);
  arr.clear();
  if (arr.size())
    return false;
  return true;
}

template <class T>
bool output_test(const T& a, const T& b) {
  my_vector<T> arr;
  arr.push_back(a);
  arr.push_back(b);
  std::stringstream s1, s2;
  s1 << arr;
  s2 << a << " " << b;
  if (s1.str() != s2.str())
    return false;
  return true;
}

template <class T>
void test_my_vector(const T& a, const T& b) {
  std::cout << "Constructors test: " << (ctors_test<T>() ? "passed." : "failed.") << std::endl;
  std::cout << "Copy test:         " << (copy_test(a, b) ? "passed." : "failed.") << std::endl;
  std::cout << "Size test:         " << (size_test(a) ? "passed." : "failed.") << std::endl;
  std::cout << "Capacity test:     " << (capacity_test(a) ? "passed." : "failed.") << std::endl;
  std::cout << "Empty test:        " << (empty_test<T>() ? "passed." : "failed.") << std::endl;
  std::cout << "Resize test:       " << (resize_test<T>() ? "passed." : "failed.") << std::endl;
  std::cout << "Reserve test:      " << (reserve_test<T>() ? "passed." : "failed.") << std::endl;
  std::cout << "Get/Set test:      " << (get_set_test(a, b) ? "passed." : "failed.") << std::endl;
  std::cout << "Push back test:    " << (push_back_test(a, b) ? "passed." : "failed.") << std::endl;
  std::cout << "Pop back test:     " << (pop_back_test<T>() ? "passed." : "failed.") << std::endl;
  std::cout << "Clear test:        " << (clear_test(a) ? "passed." : "failed.") << std::endl;
  std::cout << "Output test:       " << (output_test(a, b) ? "passed." : "failed.") << std::endl;
}

#endif