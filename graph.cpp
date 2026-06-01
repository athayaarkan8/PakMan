#include <iostream>
using namespace std;

void renderMaze(int maze[5][5]) {

    cout << "\n=== MAZE ===\n";

    for(int i = 0; i < 5; i++) {

        for(int j = 0; j < 5; j++) {

            if(maze[i][j] == 1)
                cout << "# ";
            else
                cout << ". ";
        }

        cout << endl;
    }
}

bool isValidMove(
    int maze[5][5],
    int x,
    int y
) {

    if(x < 0 || y < 0 ||
       x >= 5 || y >= 5) {

        return false;
    }

    return maze[x][y] == 0;
}

bool checkWallCollision(
    int maze[5][5],
    int x,
    int y
) {

    return !isValidMove(
        maze,
        x,
        y
    );
}

struct GraphNode {

    int x;
    int y;
};

void printGraphNodes(
    int maze[5][5]
) {

    cout << "\n=== NODE LIST ===\n";

    for(int i = 0; i < 5; i++) {

        for(int j = 0; j < 5; j++) {

            if(maze[i][j] == 0) {

                cout
                << "("
                << i
                << ","
                << j
                << ")"
                << endl;
            }
        }
    }
}