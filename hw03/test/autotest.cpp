#include "autotest.h"
#include <iostream>

int Test::failed_num = 0;
int Test::total_num = 0;

void Test::check(bool expr, const std::string &message) {
  total_num++;
  if (!expr) {
    std::cout << message << std::endl;
    failed_num++;
  }
}

void Test::show_final_result() {
  if (!failed_num) {
    std::cout << "All tests passed." << std::endl;
  }
  else {
    std::cout << "Failed " << failed_num;
    std::cout << " of " << total_num << " tests." << std::endl;
  }
}