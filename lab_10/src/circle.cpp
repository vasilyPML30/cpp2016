#include "circle.h"
#include <algorithm>
#include <cstdio>
#include <cstring>

inline int sqr(int x) {
    return x * x;
}

Circle::~Circle() {
    delete [] _label;
}

Circle::Circle(int id, int x, int y, int radius, const char* label): Figure(id, x, y) {
    _radius = radius;
    _label = new char[strlen(label) + 1];
    strcpy(_label, label);
}

Circle::Circle(const Circle &other): Figure(other) {
    _radius = other._radius;
    _label = new char[strlen(other._label) + 1];
    strcpy(_label, other._label);
}

Circle & Circle::operator=(Circle other) {
    std::swap(*this, other);
    return *this;
}

void Circle::print() const {
    printf("Circle %i: x = %i y = %i radius = %i label = %s\n", _id, _x, _y, _radius, _label);
}

bool Circle::is_inside(int x, int y) const {
    return sqr(x - _x) + sqr(y - _y) <= sqr(_radius);
}

void Circle::zoom(int factor) {
    _radius *= factor;
}
