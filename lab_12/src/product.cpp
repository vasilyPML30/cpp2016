#include "product.h"
#include <algorithm>
#include <cstring>

Product::Product() {
  name_ = new char[1];
  *name_ = 0;
  quantity_ = price_ = 0;
}

Product& Product::operator=(Product other) {
  std::swap(name_, other.name_);
  std::swap(quantity_, other.quantity_);
  std::swap(price_, other.price_);
  return *this;
}

Product::Product(const Product& other) {
  name_ = new char[strlen(other.name_) + 1];
  strcpy(name_, other.name_);
  quantity_ = other.quantity_;
  price_ = other.price_;
}

Product::Product(const char* name, int quantity, double price) {
  name_ = new char[strlen(name) + 1];
  strcpy(name_, name);
  quantity_ = quantity;
  price_ = price;
}

Product::~Product() {
  delete [] name_;
}

bool Product::operator!=(Product other) const {
  return strcmp(name_, other.name_) && quantity_ != other.quantity_ && price_ != other.price_;
}

std::ostream& operator<<(std::ostream& out, const Product& p) {
    return out << p.name_ << " " << p.quantity_ << " " << p.price_;
}
