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
  BitReader &operator>>(unsigned char &symbol);
  BitReader &operator>>(uint32_t &number);

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
  BitWriter &operator<<(unsigned char symbol);
  BitWriter &operator<<(uint32_t number);

  void flush();
  size_t tellp();

private:
  BitWriter(const BitWriter &t);
  BitWriter &operator=(const BitWriter &t);

  unsigned char _buffer;
  std::ofstream _out_file;
  std::size_t _pos;
};

#endif