#include "figure.h"

Figure::Figure(int id, int x, int y) {
    _id = id;
    _x = x;
    _y = y;
}

Figure::~Figure() {}

void Figure::move(int new_x, int new_y) {
    _x = new_x;
    _y = new_y;
}

int Figure::get_id() {
    return _id;
}