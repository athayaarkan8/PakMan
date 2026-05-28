#include <iostream>
using namespace std;


struct Node {
    int x;
    int y;
};

class Queue {

private:

    Node data[100];
    int front;
    int rear;

public:

    Queue() {
        front = 0;
        rear = 0;
    }

    void enqueue(Node n) {

        data[rear] = n;
        rear++;
    }

    Node dequeue() {

        Node temp = data[front];
        front++;

        return temp;
    }

    bool isEmpty() {

        return front == rear;
    }
};

bool visited[SIZE][SIZE];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void resetVisited() {

    for(int i = 0; i < SIZE; i++) {

        for(int j = 0; j < SIZE; j++) {

            visited[i][j] = false;
        }
    }
}

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