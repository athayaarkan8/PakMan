#include <iostream>
#include "../game.h"
#include "../maze/mazeData.h"

using namespace std;

GameData::GameData()
    : player(1, 1),
      ghost(SIZE - 2, SIZE - 2),
      packageX(SIZE - 2),
      packageY(1),
      deliveryX(1),
      deliveryY(SIZE - 2),
      hasPackage(false),
      gameRunning(false),
      state(MENU)
{
    initializeMaze(maze, difficulty);
}

void loadLevel(
    GameData &game,
    int difficulty)
{
    const MazeLevel *level;

    if (difficulty == 1)
    {
        level = &EASY_LEVELS[rand() % 3];
    }
    else if (difficulty == 2)
    {
        level = &MEDIUM_LEVELS[rand() % 3];
    }
    else
    {
        level = &HARD_LEVELS[rand() % 3];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            game.maze[i][j] =
                level->maze[i][j];
        }
    }

    game.player =
        Player(
            level->playerX,
            level->playerY);

    game.ghost =
        Ghost(
            level->ghostX,
            level->ghostY);

    game.packageX = level->packageX;
    game.packageY = level->packageY;

    game.deliveryX = level->deliveryX;
    game.deliveryY = level->deliveryY;
}

void initializeGame(
    GameData &game,
    int difficulty)
{
    game = GameData();

    loadLevel(
        game,
        difficulty);

    game.state = PLAYING;
    game.gameRunning = true;
}

void renderGame(const GameData &game)
{
    system("cls");
    cout << "\nRewind Energy: " << game.player.getEnergy();
    cout
        << " | Recharge: "
        << game.player.getStepCounter()
        << "/10";
    cout << " | Paket: " << (game.hasPackage ? "Sudah diambil" : "Belum") << "\n\n";

    renderMaze(
        game.maze,
        game.difficulty,
        game.player.getX(),
        game.player.getY(),
        game.ghost.x,
        game.ghost.y,
        game.packageX,
        game.packageY,
        game.deliveryX,
        game.deliveryY,
        game.hasPackage);

    if (game.state == PAUSED)
    {
        cout << "\n[PAUSED]\n";
    }
}

void handlePlayerInput(GameData &game, char input)
{
    if (input == 'z')
    {
        game.player.rewind();
    }
    else
    {
        game.player.move(input, game.maze);
    }

    if (!game.hasPackage &&
        game.player.getX() == game.packageX &&
        game.player.getY() == game.packageY)
    {
        game.hasPackage = true;
    }
}

bool checkCollision(const GameData &game)
{
    return game.player.getX() == game.ghost.x &&
           game.player.getY() == game.ghost.y;
}

bool checkWinCondition(const GameData &game)
{
    return game.hasPackage &&
           game.player.getX() == game.deliveryX &&
           game.player.getY() == game.deliveryY;
}

void updateGameState(GameData &game)
{
    if (checkCollision(game))
    {
        game.state = GAME_OVER;
        return;
    }

    if (!game.player.hasJustRewinded())
    {
        game.ghost.setDifficulty(game.difficulty);

        game.ghost.update(
            game.maze,
            game.player.getX(),
            game.player.getY());
    }

    if (checkCollision(game))
    {
        game.state = GAME_OVER;
    }
    else if (checkWinCondition(game))
    {
        game.state = WIN;
    }
    game.player.resetRewindFlag();
}
