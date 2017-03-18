#include "employees.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
  EmployeesArray arr;
  while (true) {
    string command;
    cin >> command;
    if (!strcmp(command.c_str(), "exit"))
      break;
    else if (!strcmp(command.c_str(), "list"))
      cout << arr << endl;
    else if (!strcmp(command.c_str(), "add")) {
      int type;
      cin >> type;
      Employee *emp = (type == 1 ? (Employee *) new Developer() : (Employee *) new SalesManager());
      cin >> *emp;
      arr.add(emp);
    }
    else if (!strcmp(command.c_str(), "load")) {
      string filename;
      cin >> filename;
      ifstream fin(filename.c_str());
      fin >> arr;
    }
    else if (!strcmp(command.c_str(), "save")) {
      string filename;
      cin >> filename;
      ofstream fout(filename.c_str());
      fout << arr;
    }
  }
  return 0;
}