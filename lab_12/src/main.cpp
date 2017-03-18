#include <iostream>

#include "product.h"
#include "my_vector.h"
#include "tests.h"

int main() {
  std::cout << std::endl << "=========Testing my_vector<int>=========" << std::endl << std::endl;
  test_my_vector<int>(5, 10);
  std::cout << std::endl << "=========Testing my_vector<Product>=========" << std::endl << std::endl;
  test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
  return 0;
}

