#ifndef HUFFMAN_TEST_H_
#define HUFFMAN_TEST_H_

#include <string>
#include "../src/huffman.h"
#include "../src/bitstream.h"
#include "autotest.h"

class HuffmanTest: public Test {
public:

  HuffmanTest(const std::string &tests_data_dir,
              std::size_t tests_count);

  void test_encode() const;
  void test_decode() const;
  void run_all_tests() const;

private:
  void do_encoding(const std::string &test_case) const;
  void do_decoding(const std::string &test_case) const;
  bool compare_files(const std::string &left_file_name,
                     const std::string &right_file_name) const;

  std::string _tests_data_dir;
  std::size_t _tests_count;
};

#endif