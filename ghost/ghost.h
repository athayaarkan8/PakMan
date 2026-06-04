#ifndef GHOST_H
#define GHOST_H

#include "bfs.h"

class Ghost {

public:

    int x;
    int y;

    int detectionRadius;

    Ghost(int startX, int startY);

    int distanceToPlayer(int playerX, int playerY);

    void patrol();

    void chase();

    void update(
        int maze[SIZE][SIZE],
        int playerX,
        int playerY
    );

    void setDifficulty(int level);
};

#endif