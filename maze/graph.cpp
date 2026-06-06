#include <iostream>
#include <cstdlib>
#include <ctime>
#include "graph.h"
#include "mazeData.h"
#include "../ghost/bfs.h"

using namespace std;

void generateRandomWalls(int maze[SIZE][SIZE], int wallCount)
{
    // Kosongkan area dalam
    for (int i = 1; i < SIZE - 1; i++)
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            maze[i][j] = 0;
        }
    }

    for (int k = 0; k < wallCount; k++)
    {
        int x = rand() % (SIZE - 3) + 1;
        int y = rand() % (SIZE - 3) + 1;

        int panjang = rand() % 4 + 1;

        for (int p = 0; p < panjang; p++)
        {
            if (y + p < SIZE - 1)
            {
                maze[x][y + p] = 1;
            }
        }
    }
}

void initializeMaze(
    int maze[SIZE][SIZE],
    int difficulty)
{
    static bool seeded = false;

    if (!seeded)
    {
        srand(time(NULL));
        seeded = true;
    }

    int selected = rand() % 3;

    const int (*source)[SIZE];
    const MazeLevel *selectedLevel;

    if (difficulty == 1)
    {
        selectedLevel =
            &EASY_LEVELS[rand() % 3];
    }
    else if (difficulty == 2)
    {
        selectedLevel =
            &MEDIUM_LEVELS[rand() % 3];
    }
    else
    {
        selectedLevel =
            &HARD_LEVELS[rand() % 3];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            maze[i][j] = source[i][j];
        }
    }
}

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
    bool hasPackage)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            char cell = (maze[i][j] == 1) ? '#' : '.';

            if (!hasPackage &&
                i == packageX &&
                j == packageY)
            {
                cell = '$';
            }

            if (i == deliveryX &&
                j == deliveryY)
            {
                cell = '!';
            }

            if (i == ghost1X &&
                j == ghost1Y)
            {
                cell = '>';
            }

            if (difficulty >= 2 &&
                i == ghost2X &&
                j == ghost2Y)
            {
                cell = '<';
            }
            if (difficulty == 3 &&
                i == ghost3X &&
                j == ghost3Y)
            {
                cell = '^';
            }

            if (i == playerX &&
                j == playerY)
            {
                cell = 'C';
            }

            cout << cell << ' ';
        }

        cout << endl;
    }
}