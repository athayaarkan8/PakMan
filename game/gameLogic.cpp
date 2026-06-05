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
    // initializeMaze(maze, difficulty);
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
    for (int i = 0; i < 5; i++)
    {
        game.packageSpawn[i][0] =
            level->packageSpawn[i][0];

        game.packageSpawn[i][1] =
            level->packageSpawn[i][1];
    }
    game.currentPackageIndex = 0;

    game.packageX =
        game.packageSpawn[0][0];

    game.packageY =
        game.packageSpawn[0][1];

    game.player =
        Player(
            level->playerX,
            level->playerY);

    game.ghost =
        Ghost(
            level->ghostX,
            level->ghostY);

    // game.packageX = level->packageX;
    // game.packageY = level->packageY;

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
    if (difficulty == 1)
    {
        game.targetPackages = 1;
    }
    else if (difficulty == 2)
    {
        game.targetPackages = 3;
    }
    else
    {
        game.targetPackages = 5;
    }
    game.currentPackageIndex = 0;

    game.deliveredPackages = 0;
    game.state = PLAYING;
    game.gameRunning = true;
}

void renderGame(const GameData &game)
{
    system("cls");
    cout << "================================\n";
    cout << "Tingkat Kesulitan: " << game.difficulty << "\n";
    cout << "\nKesempatan Rewind: " << game.player.getEnergy();
    cout
        << " | Recharge: "
        << game.player.getStepCounter()
        << "/13";
    cout << " | Paket: " << (game.hasPackage ? "Sudah diambil" : "Belum diambil") ;
    cout
        << "\nPaket Terkirim: "
        << game.deliveredPackages
        << "/"
        << game.targetPackages << "\n\n";
    cout << "================================\n";

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
        cout << "[Q] Lanjutkan.\n";
        cout << "[C] Cara Bermain.\n";
        cout << "[X] Keluar.\n";

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
    return game.deliveredPackages >=
           game.targetPackages;
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

    if (game.hasPackage &&
        game.player.getX() == game.deliveryX &&
        game.player.getY() == game.deliveryY)
    {
        game.deliveredPackages++;

        game.hasPackage = false;

        if (game.deliveredPackages <
            game.targetPackages)
        {
            game.currentPackageIndex++;

            game.packageX =
                game.packageSpawn[game.currentPackageIndex][0];

            game.packageY =
                game.packageSpawn[game.currentPackageIndex][1];
        }
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
