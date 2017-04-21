#ifndef HUFFMAN_TEST_H_
#define HUFFMAN_TEST_H_

#include <string>
#include "../src/huffman.h"
#include "../src/bitstream.h"
#include "autotest.h"

class HuffmanTest: public Test {
public:
  void test_encode() const;
  void test_decode() const;
  void run_all_tests() const;
private:
  void do_encoding(char test_case) const;
  void do_decoding(char test_case) const;
  bool compare_files(const std::string &left_file_name,
                     const std::string &right_file_name) const;
};

#endif