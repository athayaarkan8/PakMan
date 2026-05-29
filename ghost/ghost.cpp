#include <iostream>
#include "ghost.h"
using namespace std;

Ghost::Ghost(int startX, int startY) {

    x = startX;
    y = startY;

    detectionRadius = 3;
}

int Ghost::distanceToPlayer(int playerX, int playerY) {

    int dx = x - playerX;
    if(dx < 0) dx = -dx;

    int dy = y - playerY;
    if(dy < 0) dy = -dy;

    return dx + dy;
}

void Ghost::patrol() {

    cout << "Ghost Patrol Mode" << endl;
}

void Ghost::chase() {

    cout << "Ghost Chase Mode" << endl;
}

void Ghost::update(
    int maze[SIZE][SIZE],
    int playerX,
    int playerY
) {

    int dist = distanceToPlayer(playerX, playerY);

    if(dist <= detectionRadius) {

        bool found = bfs(
            maze,
            x,
            y,
            playerX,
            playerY
        );

        if(found) {

            chase();
        }
        else {

            patrol();
        }
    }
    else {

        patrol();
    }
}

void Ghost::setDifficulty(int level) {

    if(level == 1) {

        detectionRadius = 3;
    }
    else if(level == 2) {

        detectionRadius = 5;
    }
    else {

        detectionRadius = 7;
    }
}