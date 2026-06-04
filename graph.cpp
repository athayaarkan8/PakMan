#include <iostream>
#include <cstdlib>
#include <ctime>

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

void generateMaze(int maze[5][5]) {

    srand(time(0));

    for(int i = 0; i < 5; i++) {

        for(int j = 0; j < 5; j++) {

            if(rand() % 4 == 0)
                maze[i][j] = 1;
            else
                maze[i][j] = 0;
        }
    }

    maze[0][0] = 0;
    maze[4][4] = 0;
}

void countNodes(
    int maze[5][5]
) {

    int totalNode = 0;

    for(int i = 0; i < 5; i++) {

        for(int j = 0; j < 5; j++) {

            if(maze[i][j] == 0) {

                totalNode++;
            }
        }
    }

    cout << "\n=== GRAPH INFO ===\n";
    cout << "Total Node : "
         << totalNode
         << endl;
}