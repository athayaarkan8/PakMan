#include <iostream>
using namespace std;

const int SIZE = 5;

bool bfs(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
);

class Ghost {

public:

    int x;
    int y;

    int detectionRadius;

    Ghost(int startX, int startY) {

        x = startX;
        y = startY;

        detectionRadius = 3;
    }

    int distanceToPlayer(int playerX, int playerY) {

        int dx = x - playerX;
        if(dx < 0) dx = -dx;

        int dy = y - playerY;
        if(dy < 0) dy = -dy;

        return dx + dy;
    }

    void patrol() {

        cout << "Ghost Patrol Mode" << endl;
    }

    void chase() {

        cout << "Ghost Chase Mode" << endl;
    }

    void update(
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

    void setDifficulty(int level) {

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
};