#include 

AutoPlayer::AutoPlayer(int height, int width, int length)
{
    _height = height;
    _width = width;
    _lenToWin = length;
    char *field = new int[_height * _width];
    std::fill(field, field + height * width, '.');
    _field = new int *[_height];
    for (int i = 0; i < _height; i++)
        _field[i] = &field[i * _width];
}

AutoPlayer::~AutoPlayer()
{
    delete[] _field[0];
    delete[] _field;
}