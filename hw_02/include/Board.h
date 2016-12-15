#ifndef _BOARD_H_
#define _BOARD_H_

enum state {CROSSES, NOUGHTS, DRAW, GAME};

class Board
{
public:
    Board();
    void move(int x, int y, int sign);
    bool canMove(int x, int y) const;
    state isWin() const;
    char getCell(int x, int y) const;
    static const int height = 10;
    static const int width = 10;
    static const int lenToWin = 5;
private:
    bool isInside(int x, int y) const;
    char _field[height][width];
};


#endif