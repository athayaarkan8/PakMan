#include <iostream>
#include "bfs.h"
using namespace std;

struct Node
{
    int x;
    int y;
};

class Queue
{

private:
    Node data[100];
    int front;
    int rear;

public:
    Queue()
    {
        front = 0;
        rear = 0;
    }

    void enqueue(Node n)
    {

        data[rear] = n;
        rear++;
    }

    Node dequeue()
    {

        Node temp = data[front];
        front++;

        return temp;
    }

    bool isEmpty()
    {

        return front == rear;
    }
};

bool visited[SIZE][SIZE];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void resetVisited()
{

    for (int i = 0; i < SIZE; i++)
    {

        for (int j = 0; j < SIZE; j++)
        {

            visited[i][j] = false;
        }
    }
}

struct Position
{
    int x;
    int y;
};

BFSPosition getNextMove(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
);

bool bfs(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
) {

    Queue q;

    resetVisited();

    Node start;

    start.x = ghostX;
    start.y = ghostY;

    q.enqueue(start);

    visited[ghostX][ghostY] = true;

    while(!q.isEmpty()) {

        Node current = q.dequeue();

        if(current.x == playerX &&
           current.y == playerY) {

            return true;
        }

        for(int i = 0; i < 4; i++) {

            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if(nx >= 0 &&
               ny >= 0 &&
               nx < SIZE &&
               ny < SIZE &&
               maze[nx][ny] == 0 &&
               !visited[nx][ny]) {

                visited[nx][ny] = true;

                Node next;

                next.x = nx;
                next.y = ny;

                q.enqueue(next);
            }
        }
    }

    return false;
}

BFSPosition getNextMove(
    int maze[SIZE][SIZE],
    int ghostX,
    int ghostY,
    int playerX,
    int playerY
)
{
    BFSPosition fallback;
    fallback.x = ghostX;
    fallback.y = ghostY;

    int parentX[SIZE][SIZE];
    int parentY[SIZE][SIZE];

    Queue q;

    resetVisited();

    Node start;
    start.x = ghostX;
    start.y = ghostY;

    q.enqueue(start);

    visited[ghostX][ghostY] = true;

    parentX[ghostX][ghostY] = -1;
    parentY[ghostX][ghostY] = -1;

    while(!q.isEmpty())
    {
        Node current = q.dequeue();

        if(current.x == playerX &&
           current.y == playerY)
        {
            int cx = playerX;
            int cy = playerY;

            while(!(parentX[cx][cy] == ghostX &&
                    parentY[cx][cy] == ghostY))
            {
                int px = parentX[cx][cy];
                int py = parentY[cx][cy];

                if(px == -1 || py == -1)
                {
                    break;
                }

                cx = px;
                cy = py;
            }

            BFSPosition next;
            next.x = cx;
            next.y = cy;

            return next;
        }

        for(int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if(nx >= 0 &&
               ny >= 0 &&
               nx < SIZE &&
               ny < SIZE &&
               maze[nx][ny] == 0 &&
               !visited[nx][ny])
            {
                visited[nx][ny] = true;

                parentX[nx][ny] = current.x;
                parentY[nx][ny] = current.y;

                Node next;
                next.x = nx;
                next.y = ny;

                q.enqueue(next);
            }
        }
    }

    return fallback;
}