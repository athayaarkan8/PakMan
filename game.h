#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "game/stack.h"
#include "ghost/bfs.h"
#include "ghost/ghost.h"
#include "maze/graph.h"
#include "player/player.h"

enum GameState
{
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN
};

struct GameData
{
    int maze[SIZE][SIZE];
    int difficulty;
    Player player;
    Ghost ghost1;
    Ghost ghost2;
    Ghost ghost3;
    int packageX;
    int packageY;
    int deliveryX;
    int deliveryY;
    bool hasPackage;
    int deliveredPackages;
    int deliveryPatrolIndex;
    int targetPackages;
    int currentPackageIndex;
    int packageSpawn[5][2];
    bool gameRunning;
    GameState state;

    GameData();
};

void initializeGame(GameData &game, int difficulty);
void loadLevel(
    GameData &game,
    int difficulty);
void renderGame(const GameData &game);
void handlePlayerInput(GameData &game, char input);
void updateGameState(GameData &game);
bool checkCollision(const GameData &game);
bool checkWinCondition(const GameData &game);

#endif
