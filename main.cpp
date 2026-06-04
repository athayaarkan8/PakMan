#include <iostream>
using namespace std;

#include "ghost.cpp"
#include "bfs.cpp"
#include "graph.cpp"

int main() {

    int maze[SIZE][SIZE];
    
    generateMaze(maze);

    renderMaze(maze);

    printGraphNodes(maze);

    printConnections(maze);

    countNodes(maze);

    cout << "\n=== MOVEMENT TEST ===\n";

    if(isValidMove(maze,2,2))
        cout << "Move Valid" << endl;

    if(checkWallCollision(maze,0,3))
        cout << "Wall Collision" << endl;
    
    Ghost ghost(0,0);

    int playerX = 2;
    int playerY = 2;

    ghost.setDifficulty(2);

    ghost.update(
        maze,
        playerX,
        playerY
    );

    return 0;
}