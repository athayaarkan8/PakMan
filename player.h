#ifndef PLAYER_H
#define PLAYER_H

#include "stack.h"

const int SIZE = 5;

class Player
{
private:
    int x;
    int y;

    int rewindEnergy;

    Stack history;

public:
    Player(
        int startX,
        int startY
    );

    void move(
        char input,
        int maze[SIZE][SIZE]
    );

    void rewind();

    int getX();

    int getY();

    int getEnergy();
};

#endif