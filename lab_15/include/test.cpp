#include <iostream>

using namespace std;

template <class T>
void test(T func) {
  int num = 8;
  for (int i = 0; i < 5; ++i)
    func();
}

int main() {
  int num = 7;
  test([num] () { int a = num; cout << a++ << endl; });
  return 0;
}