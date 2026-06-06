#ifndef GRAPH_H
#define GRAPH_H
#include "../common.h"

void initializeMaze(int maze[SIZE][SIZE], int difficulty);

// bool isValidMove(
//     int maze[SIZE][SIZE],
//     int x,
//     int y
// );

// bool checkWallCollision(
//     int maze[SIZE][SIZE],
//     int x,
//     int y
// );

void renderMaze(
    const int maze[SIZE][SIZE],
    int difficulty,
    int playerX,
    int playerY,
    int ghost1X,
    int ghost1Y,
    int ghost2X,
    int ghost2Y,
    int ghost3X,
    int ghost3Y,
    int packageX,
    int packageY,
    int deliveryX,
    int deliveryY,
    bool hasPackage);

void printGraphNodes(int maze[SIZE][SIZE]);

void printConnections(int maze[SIZE][SIZE]);

#endif