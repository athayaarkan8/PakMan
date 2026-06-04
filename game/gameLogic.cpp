#include <iostream>
#include "../game.h"

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

void initializeGame(GameData &game, int difficulty)
{
    game = GameData();

    game.difficulty = difficulty;

    initializeMaze(
        game.maze,
        difficulty
    );

    game.state = PLAYING;
    game.gameRunning = true;
}

void renderGame(const GameData &game)
{
    system("cls"); 
    cout << "\nRewind Energy: " << game.player.getEnergy();
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

    game.ghost.setDifficulty(2);
    game.ghost.update(game.maze, game.player.getX(), game.player.getY());

    if (checkCollision(game))
    {
        game.state = GAME_OVER;
    }
    else if (checkWinCondition(game))
    {
        game.state = WIN;
    }
}
