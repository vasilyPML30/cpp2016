#include "bitstream.h"
#include <climits>
#include <iostream>

BitReader::BitReader(const std::string &file_name):
                      _in_file(file_name.c_str()) {
  if (!_in_file) {
    throw std::ios_base::failure("can not open input file");
  }
  _in_file.exceptions(std::ios_base::eofbit | std::ios_base::badbit);
  _buffer = _pos = 0;
  read_next_byte();
}

BitReader &BitReader::operator>>(bool &bit) {
  if (_pos >= CHAR_BIT) {
    read_next_byte();
  }
  bit = _buffer & (1 << (CHAR_BIT - 1 - _pos++));
  return *this;
}

std::size_t BitReader::tellg() {
  return _in_file.tellg();
}

void BitReader::read_next_byte() {
  unsigned char tmp_buffer = _in_file.get();
  _pos = 0;
  _buffer = tmp_buffer;
}

BitWriter::BitWriter(const std::string &file_name):
                     _out_file(file_name.c_str()) {
  if (!_out_file) {
    throw std::ios_base::failure("can not open output file");
  }
  _out_file.exceptions(std::ios_base::eofbit | std::ios_base::badbit);
  _buffer = _pos = 0;
}

BitWriter::~BitWriter() {
  try {
    flush();
  }
  catch(std::ios_base::failure error) {
    std::cerr << error.what() << std::endl;
  }
}

BitWriter &BitWriter::operator<<(bool bit) {
  if (_pos >= CHAR_BIT) {
    flush();
  }
  _buffer |= (bit << (CHAR_BIT - 1 - _pos++));
  return *this;
}

BitWriter &BitWriter::operator<<(const std::vector<bool> &array) {
  for (std::size_t i = 0; i < array.size(); i++) {
    *this << array[i];
  }
  return *this;
}

void BitWriter::flush() {
  if (_pos) {
    _out_file.put(_buffer);
  }
  _pos = _buffer = 0;
}

size_t BitWriter::tellp() {
  return _out_file.tellp();
}
