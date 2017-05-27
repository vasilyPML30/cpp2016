#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <cstddef>

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:
  virtual const T& operator*() const = 0;
  virtual enumerator<T>& operator++() = 0;
  virtual operator bool() const = 0;

  auto drop(size_t count) {
    return drop_enumerator<T>(*this, count);
  }

  auto take(size_t count) {
    return take_enumerator<T>(*this, count);
  }

  template<typename U = T, typename F>
  auto select(F func) {
    return select_enumerator<U, T, F>(*this, func);
  }

  template<typename F>
  auto until(F func) {
    return until_enumerator<T, F>(*this, func);
  }

  auto until_eq(const T &v) {
    return until([v] (const T &x) { return x == v; });
  }

  template<typename F>
  auto where(F func) {
    return where_enumerator<T, F>(*this, func);
  }

  auto where_neq(const T &v) {
    return where([v] (const T &x) { return x != v; });
  }

  std::vector<T> to_vector() {
    std::vector<T> result;
    while (*this) {
      result.push_back(**this);
      ++(*this);
    }
    return result;
  }

  template<typename Iter>
  void copy_to(Iter it) {
    while (*this) {
      *it = **this;
      ++(*this);
    }
  } 
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
  const T& operator*() const override {
    return *begin_;
  }

  enumerator<T>& operator++() override {
    ++begin_;
    return *this;
  }

  operator bool() const override {
    return begin_ != end_;
  }
  range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) { }

private:
  Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
  return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
  const T& operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    ++parent_;
    return *this;
  }

  operator bool() const override {
    return parent_;
  }

  drop_enumerator(enumerator<T> &parent, size_t count) : parent_(parent) {
    for (size_t i = 0; i < count; i++)
      ++parent_;
  }

private:
  enumerator<T>& parent_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
  const T& operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    ++taken_;
    if (!*this)
      return *this;
    ++parent_;
    return *this;
  }

  operator bool() const override {
    return parent_ && taken_ < count_;
  }

  take_enumerator(enumerator<T> &parent, size_t count) :
                        parent_(parent), count_(count) { }

private:
  enumerator<T>& parent_;
  size_t taken_ = 0;
  size_t count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
  const T& operator*() const override {
    return current_;
  }

  enumerator<T>& operator++() override {
    ++parent_;
    apply();
    return *this;
  }

  operator bool() const override {
    return parent_;
  }

  select_enumerator(enumerator<U> &parent, F func) :
                      parent_(parent), func_(std::move(func)) {
    apply();
  }

private:
  void apply() {
    if (parent_)
      current_ = func_(*parent_);
  }

  enumerator<U>& parent_;
  F func_;
  T current_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
  const T& operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    if (!*this)
      return *this;
    ++parent_;
    update();
    return *this;
  }

  operator bool() const override {
    return parent_ && !ended_;
  }

  until_enumerator(enumerator<T> &parent, F predicate) :
                parent_(parent), predicate_(std::move(predicate)) {
    update();
  }

private:
  void update() {
    if (parent_ && !ended_)
      ended_ = predicate_(*parent_);
  }

  enumerator<T>& parent_;
  F predicate_;
  bool ended_ = false;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
  const T& operator*() const override {
    return *parent_;
  }

  enumerator<T>& operator++() override {
    ++parent_;
    get_next();
    return *this;
  }

  operator bool() const override {
    return parent_;
  }

  where_enumerator(enumerator<T> &parent, F predicate) :
                parent_(parent), predicate_(std::move(predicate)) {
    get_next();
  }

private:
  void get_next() {
    while (parent_ && !predicate_(*parent_))
      ++parent_;
  }

  enumerator<T>& parent_;
  F predicate_;
};

#endif
