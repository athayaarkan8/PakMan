#ifndef GAME_H
#define GAME_H

// Define ukuran maze
#define SIZE 5

// Include semua header modul
#include "player/player.h"
#include "ghost/ghost.h"
#include "ghost/bfs.h"
#include "game/stack.h"
#include "maze/graph.h"

// Struktur game global
struct GameData {
    int maze[SIZE][SIZE];
    Player player;
    Ghost ghost;
    Stack<Position> rewindStack;
    bool isRunning;
    int timeRemaining;
};

#endif