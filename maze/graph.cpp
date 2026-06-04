#include <iostream>
#include "graph.h"

using namespace std;

void initializeMaze(int maze[SIZE][SIZE])
{
    int defaultMaze[SIZE][SIZE] =
    {
        {0,0,0,1,0},
        {1,0,0,1,0},
        {0,0,0,0,0},
        {0,1,1,0,1},
        {0,0,0,0,0}
    };

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            maze[i][j] = defaultMaze[i][j];
        }
    }
}

void renderMaze(
    const int maze[SIZE][SIZE],
    int playerX,
    int playerY,
    int ghostX,
    int ghostY,
    int packageX,
    int packageY,
    int deliveryX,
    int deliveryY,
    bool hasPackage
)
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            char cell = (maze[i][j] == 1) ? '#' : '.';

            if(!hasPackage &&
               i == packageX &&
               j == packageY)
            {
                cell = '$';
            }

            if(i == deliveryX &&
               j == deliveryY)
            {
                cell = '!';
            }

            if(i == ghostX &&
               j == ghostY)
            {
                cell = '>';
            }

            if(i == playerX &&
               j == playerY)
            {
                cell = 'C';
            }

            cout << cell << ' ';
        }

        cout << endl;
    }
}

// bool isValidMove(
//     int maze[SIZE][SIZE],
//     int x,
//     int y
// ) {

//     if(x < 0 || y < 0 ||
//        x >= SIZE || y >= SIZE) {

//         return false;
//     }

//     return maze[x][y] == 0;
// }

// bool checkWallCollision(
//     int maze[SIZE][SIZE],
//     int x,
//     int y
// ) {

//     return !isValidMove(
//         maze,
//         x,
//         y
//     );
// }

// struct GraphNode {

//     int x;
//     int y;
// };

// void printGraphNodes(
//     int maze[SIZE][SIZE]
// ) {

//     cout << "\n=== NODE LIST ===\n";

//     for(int i = 0; i < SIZE; i++) {

//         for(int j = 0; j < SIZE; j++) {

//             if(maze[i][j] == 0) {

//                 cout
//                 << "("
//                 << i
//                 << ","
//                 << j
//                 << ")"
//                 << endl;
//             }
//         }
//     }
// }

// void printConnections(
//     int maze[SIZE][SIZE]
// ) {

//     cout << "\n=== NODE CONNECTIONS ===\n";

//     int dx[4] = {-1, 1, 0, 0};
//     int dy[4] = {0, 0, -1, 1};

//     for(int i = 0; i < SIZE; i++) {

//         for(int j = 0; j < SIZE; j++) {

//             if(maze[i][j] == 0) {

//                 cout
//                 << "("
//                 << i
//                 << ","
//                 << j
//                 << ") -> ";

//                 for(int k = 0; k < 4; k++) {

//                     int nx = i + dx[k];
//                     int ny = j + dy[k];

//                     if(nx >= 0 &&
//                        ny >= 0 &&
//                        nx < SIZE &&
//                        ny < SIZE &&
//                        maze[nx][ny] == 0) {

//                         cout
//                         << "("
//                         << nx
//                         << ","
//                         << ny
//                         << ") ";
//                     }
//                 }

//                 cout << endl;
//             }
//         }
//     }
// }
