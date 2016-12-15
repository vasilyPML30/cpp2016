#include "Board.h"
#include <algorithm>

Board::Board()
{
    std::fill(*_field, *_field + height * width, '.');
}

void Board::move(int x, int y, int sign)
{
    _field[y][x] = sign;
}

bool Board::canMove(int x, int y) const
{
    return  isInside(x, y) && _field[y][x] == '.';
}

state Board::isWin() const
{
    bool draw = true;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            char sign = _field[y][x];
            bool rightWin = true;
            bool downWin = true;
            bool diagDownWin = true;
            bool diagUpWin = true;
            if (sign == '.')
            {
                draw = false;
                continue;
            }
            for (int shift = 0; shift < lenToWin; shift++)
            {
                if (width <= x + shift || _field[y][x + shift] != sign)
                    rightWin = false;
                if (height <= y + shift || _field[y + shift][x] != sign)
                    downWin = false;
                if (width <= x + shift || height <= y + shift ||
                    _field[y + shift][x + shift] != sign)
                    diagDownWin = false;
                if (width <= x + shift || y - shift < 0 ||
                    _field[y - shift][x + shift] != sign)
                    diagUpWin = false;
            }
            if (rightWin || downWin || diagDownWin || diagUpWin)
                return sign == 'X' ? CROSSES : NOUGHTS;
        }
    return draw ? DRAW : GAME;
}

char Board::getCell(int x, int y) const
{
    if (isInside(x, y))
        return _field[y][x];
    return '?';
}

bool Board::isInside(int x, int y) const
{
    return 0 <= x && x < width && 0 <= y && y < height;
}