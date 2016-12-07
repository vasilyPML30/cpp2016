#include "rectangle.h"
#include <cstdio>

Rectangle::Rectangle(int id, int x, int y, int width, int height): Figure(id, x, y) {
    _width = width;
    _height = height;
}

void Rectangle::print() const {
    printf("Rectangle %i: x = %i y = %i width = %i height = %i\n", _id, _x, _y, _width, _height);
}

bool Rectangle::is_inside(int x, int y) const {
    return _x * 2 - _width  <= x * 2 && x * 2 <= _x * 2 + _width &&
           _y * 2 - _height <= y * 2 && y * 2 <= _y * 2 + _height;
}

void Rectangle::zoom(int factor) {
    _width *= factor;
    _height *= factor;
}
