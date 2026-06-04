#ifndef MAZEDATA_H
#define MAZEDATA_H

#include "../common.h"

struct MazeLevel
{
    int maze[SIZE][SIZE];

    int playerX;
    int playerY;

    int ghostX;
    int ghostY;

    int packageX;
    int packageY;

    int deliveryX;
    int deliveryY;
};

extern const MazeLevel EASY_LEVELS[3];
extern const MazeLevel MEDIUM_LEVELS[3];
extern const MazeLevel HARD_LEVELS[3];

#endif