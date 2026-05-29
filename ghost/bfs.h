#ifndef BFS_H
#define BFS_H

const int SIZE = 5;

bool bfs(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
);

#endif