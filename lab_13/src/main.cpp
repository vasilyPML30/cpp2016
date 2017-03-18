#include <cstddef>
#include <cassert>
#include "my_array.h"

using namespace std;

template<std::size_t N>
void test_core_bool() {
  my_array<bool, N> a;
  const my_array<bool, N> &ca = a;
  assert(sizeof(a) == (N + 7) / 8);
  for (size_t i = 0; i < N; ++i)
    assert(a[i] == false && ca.at(i) == false);
  a.at(0);
  ca.at(0);
  a[0] = true;
  assert(a.at(0) && ca[0] && a[0]);
  a[2] = a[0];
  a[3] = ca[0];
  assert(a[2] && a[3]);
}

template<typename T, std::size_t N>
void test_core() {
  my_array<T, N> a;
  assert(a.size() == N);
  const my_array<T, N> &ca = a;
  assert(!a.empty());
  assert(!ca.empty());
  assert(a.size() == N);
  assert(ca.size() == N);
  (void)static_cast<const T &>(a[0]);
  (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.fill(T());
  a.at(0);
  ca.at(0);
  a[0];
  a[1] = ca[0];
  my_array<T, N> b = a;
  my_array<T, N> cb = ca;
  a[1] = b[0];
  cb[1] = a[0];
  a[0] = T();
  a[0] = a[0];
  a[0] = ca[0];
}

class NonCopyable {
 public:
  NonCopyable() {}
 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable);
};

int main() {
  test_core<int, 10>();
  test_core<bool, 10>();
  test_core_bool<10>();
  test_core<NonCopyable, 10>();

  test_assign<int, 10>();
  test_assign<bool, 10>();
}
