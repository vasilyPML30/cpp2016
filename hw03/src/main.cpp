#include "huffman.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  bool encode = false, decode = false, correct_input = true;
  std::string in_file, out_file;
  if (argc != 6)
    correct_input = false;
  for (std::size_t i = 1; i < 6; i++) {
    if (argv[i] == std::string("-c"))
      encode = true;
    else if (argv[i] == std::string("-u"))
      decode = true;
    else if (argv[i] == std::string("-f") ||
             argv[i] == std::string("--file")) {
      if (i == 5)
        correct_input = false;
      else
        in_file = argv[++i];
    }
    else if (argv[i] == std::string("-o") ||
             argv[i] == std::string("--output")) {
      if (i == 5)
        correct_input = false;
      else
        out_file = argv[++i];
    }
    else
      correct_input = false;
  }
  if (encode && decode)
    correct_input = false;
  if (in_file == "" || out_file == "" || !correct_input) {
    std::cout << "incorrect parameters" << std::endl;
    return 1;
  }
  if (encode) {
    HuffmanEncoder encoder(in_file);
    encoder.encode(out_file, std::cout);
  }
  else {
    HuffmanDecoder decoder(in_file);
    decoder.decode(out_file, std::cout);
  }
  return 0;
}