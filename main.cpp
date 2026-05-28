#include <iostream>
using namespace std;

#include "ghost.cpp"
#include "bfs.cpp"

int main() {

    int maze[SIZE][SIZE] = {

        {0,0,0,1,0},
        {1,0,0,1,0},
        {0,0,0,0,0},
        {0,1,1,0,1},
        {0,0,0,0,0}
    };

    Ghost ghost(0,0);

    int playerX = 2;
    int playerY = 2;

    ghost.setDifficulty(2);

    ghost.update(
        maze,
        playerX,
        playerY
    );

    return 0;
}