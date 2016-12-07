#pragma once

#include "figure.h"

class Rectangle : public Figure {
  public:
    Rectangle(int id, int x, int y, int width, int height);
    void print() const;
    bool is_inside(int x, int y) const;
    void zoom(int factor);
  private:
    int _width;
    int _height;
};
