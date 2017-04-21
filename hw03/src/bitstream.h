#ifndef BITSTREAM_H_
#define BITSTREAM_H_

#include <string>
#include <fstream>
#include <vector>

typedef unsigned int uint32_t;

class BitReader {
public:
  BitReader(const std::string &file_name);

  BitReader &operator>>(bool &bit);

  template <typename T>
  BitReader &operator>>(T &value);

  std::size_t tellg();
  void read_next_byte();

private:
  BitReader(const BitReader &t);
  BitReader &operator=(const BitReader &t);

  unsigned char _buffer;
  std::ifstream _in_file;
  std::size_t _pos;
};

class BitWriter {
public:
  BitWriter(const std::string &file_name);
  ~BitWriter();

  BitWriter &operator<<(bool bit);
  BitWriter &operator<<(const std::vector<bool> &array);
  
  template<typename T>
  BitWriter &operator<<(const T &value);

  void flush();
  size_t tellp();

private:
  BitWriter(const BitWriter &t);
  BitWriter &operator=(const BitWriter &t);

  unsigned char _buffer;
  std::ofstream _out_file;
  std::size_t _pos;
};

template<typename T>
BitReader &BitReader::operator>>(T &value) {
  std::size_t size = sizeof(T) * 8;
  T tmp_value = 0;
  for (std::size_t i = 0; i < size; i++) {
    bool bit;
    *this >> bit;
    tmp_value |= (bit << (size - 1 - i));
  }
  value = tmp_value;
  return *this;
}

template<typename T>
BitWriter &BitWriter::operator<<(const T &value) {
  std::size_t size = sizeof(T) * 8;
  for (std::size_t i = 0; i < size; i++) {
    *this << (bool)(value & (1 << (size - 1 - i)));
  }
  return *this;
}

#endif