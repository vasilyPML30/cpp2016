#ifndef TEST_H_
#define TEST_H_

#include <cstddef>
#include <fstream>
#include <string>

class Test {
public:
  static void check(bool expr, const std::string &message); 
  static void show_final_result();
  virtual void run_all_tests() const = 0;

private:
  static int failed_num;
  static int total_num;
};

#endif