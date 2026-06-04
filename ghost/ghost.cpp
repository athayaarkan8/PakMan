#include "ghost.h"

Ghost::Ghost(int startX, int startY)
{
    x = startX;
    y = startY;

    detectionRadius = 3;
    patrolIndex = 0;
}

int Ghost::distanceToPlayer(int playerX, int playerY)
{
    int dx = x - playerX;
    if(dx < 0) dx = -dx;

    int dy = y - playerY;
    if(dy < 0) dy = -dy;

    return dx + dy;
}

void Ghost::patrol()
{
}

void Ghost::chase()
{
}

void Ghost::update(
    int maze[SIZE][SIZE],
    int playerX,
    int playerY
) {
    int dist = distanceToPlayer(playerX, playerY);

    int moveX[4] = {-1, 1, 0, 0};
    int moveY[4] = {0, 0, -1, 1};

    int bestX = x;
    int bestY = y;

    if (dist <= detectionRadius && bfs(maze, x, y, playerX, playerY))
    {
        int bestDist = dist;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + moveX[i];
            int ny = y + moveY[i];

            if (nx >= 0 && ny >= 0 && nx < SIZE && ny < SIZE && maze[nx][ny] == 0)
            {
                int nd = (nx - playerX);
                if (nd < 0) nd = -nd;
                int md = (ny - playerY);
                if (md < 0) md = -md;
                int candidateDist = nd + md;

                if (candidateDist < bestDist)
                {
                    bestDist = candidateDist;
                    bestX = nx;
                    bestY = ny;
                }
            }
        }
    }
    else
    {
        for (int step = 0; step < 4; step++)
        {
            int i = (patrolIndex + step) % 4;
            int nx = x + moveX[i];
            int ny = y + moveY[i];

            if (nx >= 0 && ny >= 0 && nx < SIZE && ny < SIZE && maze[nx][ny] == 0)
            {
                bestX = nx;
                bestY = ny;
                patrolIndex = (i + 1) % 4;
                break;
            }
        }
    }

    x = bestX;
    y = bestY;
}

void Ghost::setDifficulty(int level)
{
    if(level == 1)
    {
        detectionRadius = 3;
    }
    else if(level == 2)
    {
        detectionRadius = 5;
    }
    else
    {
        detectionRadius = 7;
    }
}
