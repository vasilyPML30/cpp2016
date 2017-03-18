#ifndef _MY_VECTOR_IMPL_H_
#define _MY_VECTOR_IMPL_H_

template <class T>
void my_vector<T>::init(size_t sz, size_t cp) {
  size_ = sz;
  capacity_ = 0;
  array_ = NULL;
  reserve(cp);
}

template <class T>
my_vector<T>::my_vector() {
  init(0, 2);
}

template <class T>
my_vector<T>::my_vector(size_t n) {
  init(0, 2);
  resize(n);
}

template <class T>
my_vector<T>::my_vector(const my_vector& other) {
  init(0, other.capacity_);
  for (int i = 0; i < other.size(); i++)
    push_back(other[i]);
}

template <class T>
my_vector<T>& my_vector<T>::operator=(my_vector other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(array_, other.array_);
}

template <class T>
my_vector<T>::~my_vector() {
  for (int i = 0; i < size_; i++)
    array_[i].~T();
  delete [] (char*) array_;
}

template <class T>
size_t my_vector<T>::size() const {
  return size_;
}

template <class T>
size_t my_vector<T>::capacity() const {
  return capacity_;
}

template <class T>
bool my_vector<T>::empty() const {
  return !size_;
}

template <class T>
void my_vector<T>::resize(size_t n) {
  reserve(n);
  for (int i = n; i < size_; i++)
    array_[i].~T();
  for (int i = size_; i < n; i++)
    new (array_ + i) T();
  size_ = n;
}

template <class T>
void my_vector<T>::reserve(size_t n) {
  if (capacity_ >= n)
    return;
  capacity_ = std::max(capacity_, (size_t)1);
  while (capacity_ < n)
    capacity_ *= 2;
  T* new_array = (T*)new char[sizeof(T) * capacity_];
  memcpy(new_array, array_, sizeof(T) * size_);
  delete [] (char*) array_;
  array_ = new_array;
}

template <class T>
const T& my_vector<T>::operator[](size_t index) const {
  return array_[index];
}

template <class T>
T& my_vector<T>::operator[](size_t index) {
  return array_[index];
}

template <class T>
void my_vector<T>::push_back(const T& t) {
  if (size_ >= capacity_)
    reserve(capacity_ * 2);
  new (array_ + size_++) T(t);
}

template <class T>
void my_vector<T>::pop_back() {
  resize(size_ - 1);
}

template <class T>
void my_vector<T>::clear() {
  resize(0);
}

template <class T>
std::ostream& operator<<(std::ostream &out, const my_vector<T> v) {
  for (int i = 0; i < v.size(); i++) {
    out << v[i];
    if (i != v.size() - 1)
      out << " ";
  }
  return out;
}

#endif