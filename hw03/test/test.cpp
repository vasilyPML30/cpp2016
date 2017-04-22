#include "huffman_test.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "usage: ./test data_dir tests_count" << std::endl;
  }
  else {
    HuffmanTest tester(argv[1], atoi(argv[2]));
    tester.run_all_tests();
    tester.show_final_result();
  }
  return 0;
}
