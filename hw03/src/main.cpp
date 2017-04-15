#include "huffman.h"
#include <fstream>
#include <iostream>
#include <string>

int main() {
  HuffmanEncoder huff(std::string("infile"));
  huff.encode(std::string("outfile"), std::cout);
  return 0;
}