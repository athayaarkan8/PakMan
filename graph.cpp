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

void printConnections(
    int maze[5][5]
) {

    cout << "\n=== NODE CONNECTIONS ===\n";

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for(int i = 0; i < 5; i++) {

        for(int j = 0; j < 5; j++) {

            if(maze[i][j] == 0) {

                cout
                << "("
                << i
                << ","
                << j
                << ") -> ";

                for(int k = 0; k < 4; k++) {

                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    if(nx >= 0 &&
                       ny >= 0 &&
                       nx < 5 &&
                       ny < 5 &&
                       maze[nx][ny] == 0) {

                        cout
                        << "("
                        << nx
                        << ","
                        << ny
                        << ") ";
                    }
                }

                cout << endl;
            }
        }
    }
}