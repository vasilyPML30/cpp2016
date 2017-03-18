#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstring>
#include <stdexcept>

#define LEN_TO_SIZE(x) (x + 7) / 8

template<typename T, std::size_t N>
class my_array {
public:
  T& at(std::size_t index);
  const T& at(std::size_t index) const;
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;
  bool empty() const;
  std::size_t size() const;
  void fill(const T& val);
private:
  void check_range(std::size_t index) const;
  T _data[N];
};

template<std::size_t N>
class my_array<bool, N> {
public:
  
  class proxy {
  public:
    proxy(char* begin, size_t index);
    proxy operator=(bool val);
    proxy operator=(const proxy val);
    operator bool() const;
  private:
    char& _byte;
    int _bit_pos;
  };
  
  my_array();
  proxy at(std::size_t index);
  bool at(std::size_t index) const;
  proxy operator[](std::size_t index);
  bool operator[](std::size_t index) const;
  bool empty() const;
  std::size_t size() const;
  void fill(bool val);

private:

  void check_range(std::size_t index) const;
  char _data[LEN_TO_SIZE(N)];
};

#include "my_array_real.h"
#include "my_array_bool_real.h"

#endif