#include "huffman.h"
#include <fstream>
#include <iostream>
#include <string>

int main() {
  HuffmanEncoder *enc = new HuffmanEncoder(std::string("infile"));
  enc->encode(std::string("outfile"), std::cout);
  delete enc;
  HuffmanDecoder *dec = new HuffmanDecoder(std::string("outfile"));
  dec->decode(std::string("newfile"), std::cout);
  delete dec;
  return 0;
}