#ifndef BFS_H
#define BFS_H

#include "../common.h"

struct BFSPosition
{
    int x;
    int y;
};

bool bfs(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
);

BFSPosition getNextMove(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
);

#endif