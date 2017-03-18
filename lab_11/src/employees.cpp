#include "employees.h"
#include <cstring> 
#include <iostream>
#include <string>

const int32_t Developer::_type = 1;
const int32_t SalesManager::_type = 2;

EmployeesArray::EmployeesArray() {
  _capacity = 2;
  _size = 0;
  _employees = new Employee *[2];
}

void EmployeesArray::add(const Employee *emp) {
  if (_size >= _capacity) {
    _capacity *= 2;
    Employee **tmp = new Employee *[_capacity];
    memcpy(tmp, _employees, _size * sizeof(*tmp));
    delete [] _employees;
    _employees = tmp;
  }
  _employees[_size++] = (Employee *)emp;
}

EmployeesArray::~EmployeesArray() {
  for (int i = 0; i < _size; i++)
    if (_employees[i])
      delete _employees[i];
  delete [] _employees;
}

int EmployeesArray::total_salary() const {
  int total = 0;
  for (int i = 0; i < _size; i++) {
    total += _employees[i]->salary();
  }
  return total;
}

Employee::Employee() {
  _name = NULL;
  _base_salary = 0;
}

Employee::Employee(const char *name, int32_t base_salary) {
  if (name) {
    _name = new char[strlen(name) + 1];
    strcpy(_name, name);
  }
  _base_salary = base_salary;
}

Employee::~Employee() {
  delete [] _name;
}

Developer::Developer() { }

Developer::Developer(const char *name, int32_t base_salary, bool has_bonus):
                                              Employee(name, base_salary) {
  _has_bonus = has_bonus;
}

SalesManager::SalesManager() { }

SalesManager::SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price):
                                                                    Employee(name, base_salary) {
  _sold_nm = sold_nm;
  _price = price;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

int SalesManager::salary() const {
  return _base_salary + _sold_nm * _price * 0.01;
}

std::ifstream &operator>>(std::ifstream &in, Employee &emp) {
  return emp.read(in);
}

std::istream &operator>>(std::istream &in, Employee &emp) {
  return emp.read(in);
}

std::ofstream &operator<<(std::ofstream &out, const Employee &emp) {
  return emp.write(out);
}

std::ostream &operator<<(std::ostream &out, const Employee &emp) {
  return emp.write(out);
}

void Employee::read_name(std::ifstream &in) {
  std::string name;
  while (true) {
    char letter;
    in.read(&letter, sizeof(letter));
    if (!letter)
      break;
    name += letter;
  }
  delete [] _name;
  _name = new char[name.size() + 1];
  strcpy(_name, name.c_str());
}

void Employee::read_name(std::istream &in) {
  std::string name;
  in >> name;
  delete [] _name;
  _name = new char[name.size() + 1];
  strcpy(_name, name.c_str());
}

std::istream &Developer::read(std::istream &in) {
  read_name(in);
  in >> _base_salary >> _has_bonus;
  return in;
}

std::ifstream &Developer::read(std::ifstream &in) {
  read_name(in);
  in.read((char *)&_base_salary, sizeof(_base_salary));
  in.read((char *)&_has_bonus, sizeof(_has_bonus));
  return in;
}

std::ostream &Developer::write(std::ostream &out) const {
  out << "Developer" << std::endl;
  out << "Name: " << _name << std::endl;
  out << "Base Salary: " << _base_salary << std::endl;
  out << "Has bonus: " << (_has_bonus ? '+' : '-');
  return out;
}

std::ofstream &Developer::write(std::ofstream &out) const {
  out.write((char *)&_type, sizeof(_type));
  out.write(_name, strlen(_name) + 1);
  out.write((char *)&_base_salary, sizeof(_base_salary));
  out.write((char *)&_has_bonus, sizeof(_has_bonus));
  return out;
}

std::istream &SalesManager::read(std::istream &in) {
  read_name(in);
  in >> _base_salary >> _sold_nm >> _price;
  return in;
}

std::ifstream &SalesManager::read(std::ifstream &in) {
  read_name(in);
  in.read((char *)&_base_salary, sizeof(_base_salary));
  in.read((char *)&_sold_nm, sizeof(_sold_nm));
  in.read((char *)&_price, sizeof(_price));
  return in;
}

std::ostream &SalesManager::write(std::ostream &out) const {
  out << "Sales Manager" << std::endl;
  out << "Name: " << _name << std::endl;
  out << "Base Salary: " << _base_salary << std::endl;
  out << "Sold items: " << _sold_nm << std::endl;
  out << "Item price: " << _price;
  return out;
}

std::ofstream &SalesManager::write(std::ofstream &out) const {
  out.write((char *)&_type, sizeof(_type));
  out.write(_name, strlen(_name) + 1);
  out.write((char *)&_base_salary, sizeof(_base_salary));
  out.write((char *)&_sold_nm, sizeof(_sold_nm));
  out.write((char *)&_price, sizeof(_price));
  return out;
}

std::ifstream &operator>>(std::ifstream &in, EmployeesArray &arr) {
  int32_t num;
  in.read((char *)&num, sizeof(num));
  for (int i = 0; i < num; i++) {
    int32_t type;
    in.read((char *)&type, sizeof(type));
    Employee *emp = (type == 1 ? (Employee *) new Developer() : (Employee *) new SalesManager());
    in >> *emp;
    arr.add(emp);
  }
  return in;
}

std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &arr) {
  out.write((char *)&arr._size, sizeof(arr._size));
  for (int i = 0; i < arr._size; i++)
    out << *arr._employees[i];
  return out;
}

std::ostream &operator<<(std::ostream &out, const EmployeesArray &arr) {
  for (int i = 0; i < arr._size; i++) {
    out << i + 1 << ". ";
    out << *arr._employees[i] << std::endl;
  }
  out << "== Total salary: " << arr.total_salary() << std::endl;
  return out;
}
