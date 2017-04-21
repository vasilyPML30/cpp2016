#include "huffman_test.h"
#include <fstream>
#include <iostream>

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

void HuffmanTest::do_encoding(char test_case) const {
  HuffmanEncoder encoder(std::string("../test_cases/") +
                         test_case + std::string(".in"));
  encoder.encode(std::string("../test_cases/") +
                 test_case + std::string(".enc"), std::cout);
}

void HuffmanTest::do_decoding(char test_case) const {
  HuffmanDecoder decoder(std::string("../test_cases/") +
                         test_case + std::string(".out"));
  decoder.decode(std::string("../test_cases/") +
                 test_case + std::string(".dec"), std::cout);
}

void HuffmanTest::test_encode() const {
  for (char test_case = 'a'; test_case <= 'f'; test_case++) {
    try {
      do_encoding(test_case);
    }
    catch (...) {
      DO_CHECK(false);
      return;
    }
    DO_CHECK(compare_files(std::string("../test_cases/") +
                           test_case + std::string(".enc"),
                           std::string("../test_cases/") +
                           test_case + std::string(".out")));
  }
}

void HuffmanTest::test_decode() const {
  for (char test_case = 'a'; test_case <= 'f'; test_case++) {
        try {
      do_decoding(test_case);
    }
    catch (...) {
      DO_CHECK(false);
      return;
    }
    DO_CHECK(compare_files(std::string("../test_cases/") +
                           test_case + std::string(".dec"),
                           std::string("../test_cases/") +
                           test_case + std::string(".in")));
  }
}

void HuffmanTest::run_all_tests() const {
  test_encode();
  test_decode();
}
