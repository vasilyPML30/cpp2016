#include "huffman_test.h"
#include <fstream>
#include <iostream>
#include <sstream>

static std::string to_string(std::size_t value) {
  std::ostringstream str;
  str << value;
  return str.str();
}

HuffmanTest::HuffmanTest(const std::string &tests_data_dir,
                         std::size_t tests_count) {
  _tests_data_dir = tests_data_dir;
  _tests_count = tests_count;
}

bool HuffmanTest::compare_files(const std::string &left_file_name,
                                const std::string &right_file_name) const {
  std::ifstream left_file(left_file_name.c_str());
  std::ifstream right_file(right_file_name.c_str());
  while (true) {
    char left_byte = left_file.get();
    char right_byte = right_file.get();
    if (left_file.eof() || right_file.eof()) {
      return left_file.eof() == right_file.eof();
    }
    if (left_byte != right_byte)
      return false;
  }
  return true;
}

void HuffmanTest::do_encoding(const std::string &test_case) const {
  HuffmanEncoder encoder(_tests_data_dir + test_case + std::string(".in"));
  encoder.encode(_tests_data_dir + test_case + std::string(".enc"), std::cout);
}

void HuffmanTest::do_decoding(const std::string &test_case) const {
  HuffmanDecoder decoder(_tests_data_dir + test_case + std::string(".out"));
  decoder.decode(_tests_data_dir + test_case + std::string(".dec"), std::cout);
}

void HuffmanTest::test_encode() const {
  std::cout << "test encoding" << std::endl;
  for (size_t test_case = 1; test_case <= _tests_count; test_case++) {
    std::cout << "test case " << test_case << ": " << std::endl;
    try {
      do_encoding(to_string(test_case));
    }
    catch (std::ios_base::failure error) {
      check(false, error.what());
    }
    catch (std::bad_alloc error) {
      check(false, error.what());
    }
    check(compare_files(_tests_data_dir +
                        to_string(test_case) + std::string(".enc"),
                        _tests_data_dir +
                        to_string(test_case) + std::string(".out")),
                        std::string("files differ"));
  }
}

void HuffmanTest::test_decode() const {
  std::cout << "test decoding" << std::endl;
  for (size_t test_case = 1; test_case <= _tests_count; test_case++) {
    std::cout << "test case " << test_case << ": " << std::endl;
    try {
      do_decoding(to_string(test_case));
    }
    catch (std::ios_base::failure error) {
      check(false, error.what());
    }
    catch (std::bad_alloc error) {
      check(false, error.what());
    }
    check(compare_files(_tests_data_dir +
                        to_string(test_case) + std::string(".dec"),
                        _tests_data_dir +
                        to_string(test_case) + std::string(".in")),
                        std::string("files differ"));
  }
}

void HuffmanTest::run_all_tests() const {
    test_encode();
    test_decode();
}
