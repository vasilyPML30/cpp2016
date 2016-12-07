#include "scheme.h"

Scheme::Scheme(int capacity) {
    _size = 0;
    _capacity = capacity;
    _figures = new Figure*[capacity];
}

Scheme::~Scheme() {
    for (int i = 0; i < _size; i++)
        delete _figures[i];
    delete [] _figures;
}

void Scheme::push_back_figure(Figure* fg) {
    if (_size + 1 < _capacity)
        _figures[_size++] = fg;
}

void Scheme::remove_figure(int id) {
    for (int i = 0; i < _size; i++)
        if (_figures[i]->get_id() == id) {
            delete _figures[i];
            for (i++; i < _size; i++)
                _figures[i - 1] = _figures[i];
            _size--;
        }
}

void Scheme::print_all_figures() const {
    for (int i = 0; i < _size; i++)
        _figures[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    for (int i = 0; i < _size; i++)
        if (_figures[i]->get_id() == id)
            _figures[i]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) const {
    for (int i = 0; i < _size; i++)
        if (_figures[i]->is_inside(x, y))
            return _figures[i];
    return 0;
}

void Scheme::move(int id, int new_x, int new_y) {
    for (int i = 0; i < _size; i++)
        if (_figures[i]->get_id() == id)
            _figures[i]->move(new_x, new_y);
}
