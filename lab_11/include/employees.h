#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <stdint.h>

class Employee {
public:
  Employee();
  Employee(const char *, int32_t);
  ~Employee();
  void read_name(std::ifstream &);
  void read_name(std::istream &);
  virtual int salary() const = 0;
  friend std::istream &operator>>(std::istream &, Employee &);
  friend std::ifstream &operator>>(std::ifstream &, Employee &);
  friend std::ostream &operator<<(std::ostream &, const Employee &);
  friend std::ofstream &operator<<(std::ofstream &, const Employee &);
  virtual std::ifstream &read(std::ifstream &) = 0;
  virtual std::istream &read(std::istream &) = 0;
  virtual std::ofstream &write(std::ofstream &) const = 0;
  virtual std::ostream &write(std::ostream &) const = 0;
protected:
  char *_name;
  int32_t _base_salary;
private:
  Employee(const Employee &);
  void operator=(const Employee &);
};

class Developer : public Employee {
public:
  Developer();
  Developer(const char *, int32_t, bool);
  int salary() const;
  virtual std::ifstream &read(std::ifstream &);
  virtual std::istream &read(std::istream &);
  virtual std::ofstream &write(std::ofstream &) const;
  virtual std::ostream &write(std::ostream &) const;
private:
  Developer(const Developer &);
  void operator=(const Developer &);
  bool _has_bonus;
  static const int32_t _type;
};

class SalesManager : public Employee {
public:
  SalesManager();
  SalesManager(const char *, int32_t, int32_t, int32_t);
  int salary() const;
  virtual std::ifstream &read(std::ifstream &);
  virtual std::istream &read(std::istream &);
  virtual std::ofstream &write(std::ofstream &) const;
  virtual std::ostream &write(std::ostream &) const;
private:
  SalesManager(const SalesManager &);
  void operator=(const SalesManager &);
  int32_t _sold_nm, _price;
  static const int32_t _type;
};

class EmployeesArray {
public:
  EmployeesArray();
  ~EmployeesArray();
  void add(const Employee *);
  int total_salary() const;
  friend std::ifstream &operator>>(std::ifstream &, EmployeesArray &);
  friend std::ofstream &operator<<(std::ofstream &, const EmployeesArray &);
  friend std::ostream &operator<<(std::ostream &, const EmployeesArray &);
private:
  EmployeesArray(const EmployeesArray &);
  void operator=(const EmployeesArray &);
  Employee **_employees;
  int32_t _size, _capacity;
};

#endif