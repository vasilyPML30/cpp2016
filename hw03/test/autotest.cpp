#include "autotest.h"
#include <iostream>

int Test::failed_num = 0;
int Test::total_num = 0;

void Test::check(bool expr, const std::string &func,
                  const std::string &file_name, size_t line_num) {
  total_num++;
  if (!expr) {
    std::cout << "test failed: " << func << "() ";
    std::cout << "in " << file_name << ":" << line_num << std::endl;
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