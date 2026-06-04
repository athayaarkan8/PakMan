#ifndef BFS_H
#define BFS_H

#include "../common.h"

bool bfs(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
);

#endif
