#ifndef TEST_H_
#define TEST_H_

#include <cstddef>
#include <fstream>
#include <string>

#define DO_CHECK(EXPR) check(EXPR, std::string(__FUNCTION__),      \
                                   std::string(__FILE__), __LINE__)

class Test {
public:
  static void check(bool expr, const std::string &func,
                    const std::string &file_name, size_t line_num); 
  static void show_final_result();
  virtual void run_all_tests() const = 0;

private:
  static int failed_num;
  static int total_num;
};

#endif