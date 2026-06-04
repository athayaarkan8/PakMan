#ifndef GRAPH_H
#define GRAPH_H

#include "../common.h"

class Graph {
public:
    void generateMaze(int maze[SIZE][SIZE]);
    void renderMaze(int maze[SIZE][SIZE]);
};

#endif
