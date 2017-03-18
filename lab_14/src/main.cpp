#include "matrix.h"
#include <fstream>
#include <string>

std::size_t readReg() {
  char reg;
  std::cin >> reg >> reg;
  return (std::size_t)(reg - '0');
}

int main() {
  Matrix array[10];
  std::string command, fname;
  int32_t row, col;
  std::size_t reg1, reg2;
  while (true) {
    std::cin >> command;
    if (command == "load") {
      reg1 = readReg();
      std::cin >> fname;
      std::ifstream file(fname.c_str());
      file >> array[reg1];
    }
    else if (command == "print") {
      reg1 = readReg();
      std::cout << array[reg1];
    }
    else if (command == "add") {
      reg1 = readReg();
      reg2 = readReg();
      try {
        array[reg1] += array[reg2];
      }
      catch(const MatrixException &e){
        std::cout << e.what() << std::endl;
      }
    }
    else if (command == "mul") {
      reg1 = readReg();
      reg2 = readReg();
      try {
        array[reg1] *= array[reg2];
      }
      catch(const MatrixException &e){
        std::cout << e.what() << std::endl;
      }
    }
    else if (command == "elem") {
      reg1 = readReg();
      std::cin >> row >> col;
      try {
        std::cout << array[reg1].element(row, col) << std::endl;
      }
      catch(const MatrixException &e) {
        std::cout << e.what() << std::endl;
      }
    }
    else if (command == "exit")
      break;
  }
  return 0;
}