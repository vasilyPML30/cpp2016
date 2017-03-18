#ifndef _AUTO_PLAYER_H_
#define _AUTO_PLAYER_H_

class AutoPlayer
{
public:
    AutoPlayer(Board &b);
    ~AutoPlayer();
    void getMove(int &x, int &y, int sign);
private:
    AutoPlayer(const AutoPlayer &a);
    AutoPlayer & operator=(const AutoPlayer &a);
};

#endif