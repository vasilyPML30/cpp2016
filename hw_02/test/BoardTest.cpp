#include "BoardTest.h"

void BoardTest::testMove() const
{
    Board m;
    m.move(0, 0, 'X');
    DO_CHECK(m.getCell(0, 0) == 'X');
    m.move(0, 0, '.');
    DO_CHECK(m.getCell(0, 0) == '.');
    m.move(1, 1, 'O');
    DO_CHECK(m.getCell(1, 1) == 'O');
}

void BoardTest::testCanMove() const
{
    Board m;
    m.move(0, 0, 'X');
    m.move(1, 1, 'O');
    DO_CHECK(!m.canMove(0, 0));
    DO_CHECK(!m.canMove(1, 1));
    DO_CHECK(m.canMove(2, 2));
    DO_CHECK(!m.canMove(-1, -1));
    DO_CHECK(!m.canMove(-2, 1));
    DO_CHECK(!m.canMove(5,10));
    DO_CHECK(m.canMove(9, 9));
    DO_CHECK(!m.canMove(10, 10));
}

void BoardTest::fillLine(Board &m, int x, int y, int dx, int dy, char sign) const
{
    refreshBoard(m);
    for (int i = 0; i < 5; i++)
        m.move(x + dx * i, y + dy * i, sign);
}

void BoardTest::testIsWin() const
{
    Board m;
    DO_CHECK(m.isWin() == GAME);
    m.move(0, 0, 'O');
    m.move(1, 1, 'X');
    DO_CHECK(m.isWin() == GAME);
    fillLine(m, 0, 0, 1, 0, 'X');
    DO_CHECK(m.isWin() == CROSSES);
    fillLine(m, 2, 2, 0, 1, 'X');
    DO_CHECK(m.isWin() == CROSSES);
    fillLine(m, 4, 4, 1, 1, 'O');
    DO_CHECK(m.isWin() == NOUGHTS);
    fillLine(m, 5, 5, 1, -1, 'O');
    DO_CHECK(m.isWin() == NOUGHTS);
    fillLine(m, 0, 0, 2, 0, 'O');
    DO_CHECK(m.isWin() == GAME);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            m.move(i, j, ((j / 2 + i) % 2 ? 'O' : 'X'));
    DO_CHECK(m.isWin() == DRAW);
}

void BoardTest::testGetCell() const
{
    Board m;
    m.move(0, 0, 'X');
    m.move(1, 1, 'O');
    DO_CHECK(m.getCell(0, 0) == 'X');
    DO_CHECK(m.getCell(1, 1) == 'O');
    DO_CHECK(m.getCell(2, 2) == '.');
    DO_CHECK(m.getCell(10, 10) == '?');
}

void BoardTest::runAllTests() const
{
    testMove();
    testCanMove();
    testIsWin();
    testGetCell();
}

void BoardTest::refreshBoard(Board &m) const
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            m.move(i, j, '.');
}
