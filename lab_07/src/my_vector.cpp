#include "my_vector.h"

using namespace std;

void MyVector::reserve(size_t new_capacity)
{
  if (_cp < new_capacity)
  {
    _data = (int *)realloc(_data, sizeof(int) * new_capacity);
    _cp = new_capacity;
  }
}

MyVector::MyVector()
{
  _cp = _sz = 0;
  _data = NULL;
  reserve(2);
}

MyVector::MyVector(size_t init_capacity)
{
  _cp = _sz = 0;
  _data = NULL;
  reserve(init_capacity);
}

MyVector::~MyVector()
{
  free(_data);
}

void MyVector::set(size_t index, int value)
{
  assert(index < _sz);
  _data[index] = value;
}

int MyVector::get(size_t index)
{
  assert(index < _sz);
  return _data[index];
}

size_t MyVector::size()
{
  return _sz;
}

size_t MyVector::capacity()
{
  return _cp;
}

void MyVector::resize(size_t new_size)
{
  reserve(new_size);
  if (new_size > _sz)
    fill(_data + _sz, _data + new_size, 0);
  _sz = new_size;
}
  
void MyVector::push_back(int value)
{
  if (_sz >= _cp)
  {
    _cp *= 2;
    reserve(_cp);
  }
  _data[_sz++] = value;
}

void MyVector::insert(size_t index, int value)
{
  assert(index <= _sz);
  push_back(0);
  memmove(_data + index + 1, _data + index, sizeof(int) * (_sz - index));
  set(index, value);
}

void MyVector::erase(size_t index)
{
  assert(index < _sz);
  memmove(_data + index, _data + index + 1, sizeof(int) * (_sz - index));
  resize(_sz - 1);
}