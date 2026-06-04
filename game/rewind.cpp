#include <iostream>
#include "../game.h"

using namespace std;

GameData::GameData()
    : player(2, 2),
      ghost(0, 0),
      packageX(4),
      packageY(0),
      deliveryX(0),
      deliveryY(4),
      hasPackage(false),
      gameRunning(false),
      state(MENU)
{
    int defaultMaze[SIZE][SIZE] = {
        {0, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0}};

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            maze[i][j] = defaultMaze[i][j];
        }
    }
}

void initializeGame(GameData &game)
{
    game = GameData();
    game.state = PLAYING;
    game.gameRunning = true;
}

void renderGame(const GameData &game)
{
    cout << "\nRewind Energy: " << game.player.getEnergy();
    cout << " | Paket: " << (game.hasPackage ? "Sudah diambil" : "Belum") << "\n\n";

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            char cell = (game.maze[i][j] == 1) ? '#' : '.';

            if (!game.hasPackage && i == game.packageX && j == game.packageY)
            {
                cell = '$';
            }

            if (i == game.deliveryX && j == game.deliveryY)
            {
                cell = '!';
            }

            if (i == game.ghost.x && j == game.ghost.y)
            {
                cell = '>';
            }

            if (i == game.player.getX() && j == game.player.getY())
            {
                cell = 'C';
            }

            cout << cell << ' ';
        }

        cout << '\n';
    }

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
