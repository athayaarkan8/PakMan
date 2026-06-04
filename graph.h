#ifndef GRAPH_H
#define GRAPH_H

const int SIZE = 5;

class Graph {
public:
    void generateMaze(int maze[SIZE][SIZE]);
    void renderMaze(int maze[SIZE][SIZE]);
    void generateMaze(int maze[5][5]);
};

#endif