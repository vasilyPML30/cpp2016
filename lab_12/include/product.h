#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <iostream>

class Product {
public:
  Product();
  Product(const Product& other);
  Product(const char* name, int quantity, double price);
  Product& operator=(Product other);
  ~Product();

  bool operator!=(Product other) const;

  friend std::ostream& operator<<(std::ostream& out, const Product& p);

private:
  char *name_;
  int quantity_;
  double price_;
};

#endif