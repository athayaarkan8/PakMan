#ifndef PLAYER_H
#define PLAYER_H

#include "../common.h"
#include "../game/stack.h"

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

    int getX() const;

    int getY() const;

    int getEnergy() const;
};

#endif
