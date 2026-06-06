#include <iostream>
#include "../game.h"
#include "../maze/mazeData.h"

using namespace std;

GameData::GameData()
    : player(1, 1),
      ghost1(SIZE - 2, SIZE - 2),
      ghost2(1, SIZE - 2),
      ghost3(1, 1),
      packageX(SIZE - 2),
      packageY(1),
      deliveryX(1),
      deliveryY(SIZE - 2),
      hasPackage(false),
      gameRunning(false),
      state(MENU)
{
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

    game.ghost1 =
        Ghost(
            level->ghostX,
            level->ghostY);

    game.ghost2 =
        Ghost(
            level->deliveryX,
            level->deliveryY - 1);

    game.ghost3 =
        Ghost(
            game.packageSpawn[0][0],
            game.packageSpawn[0][1] - 1);

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

    game.difficulty = difficulty;
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
    game.deliveryPatrolIndex = 0;

    game.deliveredPackages = 0;
    game.state = PLAYING;
    game.gameRunning = true;
}

void renderGame(const GameData &game)
{
    system("cls");
    cout << "===============================================\n";
    cout << "Tingkat Kesulitan: " << (game.difficulty == 1 ? "Mudah" : (game.difficulty == 2 ? "Sedang" : "Sulit")) << "\n";
    cout << "\nKesempatan Rewind: " << game.player.getEnergy();
    cout
        << " | Recharge: "
        << game.player.getStepCounter()
        << "/21";
    cout
        << "\nPaket Terkirim: "
        << game.deliveredPackages
        << "/"
        << game.targetPackages << "  | ";
    cout << "Paket: " << (game.hasPackage ? "Sudah diambil" : "Belum diambil");

    cout << "\n===============================================\n\n";

    renderMaze(
        game.maze,
        game.difficulty,
        game.player.getX(),
        game.player.getY(),
        game.ghost1.x,
        game.ghost1.y,
        game.ghost2.x,
        game.ghost2.y,
        game.ghost3.x,
        game.ghost3.y,
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
    bool hitGhost1 =
        game.player.getX() == game.ghost1.x &&
        game.player.getY() == game.ghost1.y;

    bool hitGhost2 = false;

    if (game.difficulty >= 2)
    {
        hitGhost2 =
            game.player.getX() == game.ghost2.x &&
            game.player.getY() == game.ghost2.y;
    }

    bool hitGhost3 = false;

    if (game.difficulty == 3)
    {
        hitGhost3 =
            game.player.getX() == game.ghost3.x &&
            game.player.getY() == game.ghost3.y;
    }

    return hitGhost1 ||
           hitGhost2 ||
           hitGhost3;
}

bool checkWinCondition(const GameData &game)
{
    return game.deliveredPackages >=
           game.targetPackages;
}

int manhattanDistance(
    int x1,
    int y1,
    int x2,
    int y2)
{
    int dx = x1 - x2;
    if (dx < 0)
        dx = -dx;

    int dy = y1 - y2;
    if (dy < 0)
        dy = -dy;

    return dx + dy;
}

int getAvailablePatrolPoints(
    int maze[SIZE][SIZE],
    int centerX,
    int centerY,
    int patrol[4][2])
{
    int count = 0;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++)
    {
        int nx = centerX + dx[i];
        int ny = centerY + dy[i];

        if (nx >= 0 &&
            ny >= 0 &&
            nx < SIZE &&
            ny < SIZE &&
            maze[nx][ny] == 0)
        {
            patrol[count][0] = nx;
            patrol[count][1] = ny;
            count++;
        }
    }

    return count;
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
        game.ghost1.setDifficulty(game.difficulty);

        game.ghost1.update(
            game.maze,
            game.player.getX(),
            game.player.getY());

        if (game.difficulty >= 2)
        {
            int patrolX[8] =
                {
                    game.deliveryX - 1,
                    game.deliveryX - 1,
                    game.deliveryX,
                    game.deliveryX + 1,
                    game.deliveryX + 1,
                    game.deliveryX + 1,
                    game.deliveryX,
                    game.deliveryX - 1};

            int patrolY[8] =
                {
                    game.deliveryY,
                    game.deliveryY + 1,
                    game.deliveryY + 1,
                    game.deliveryY + 1,
                    game.deliveryY,
                    game.deliveryY - 1,
                    game.deliveryY - 1,
                    game.deliveryY - 1};

            int nextX =
                patrolX[game.deliveryPatrolIndex];

            int nextY =
                patrolY[game.deliveryPatrolIndex];

            if (nextX >= 0 &&
                nextY >= 0 &&
                nextX < SIZE &&
                nextY < SIZE &&
                game.maze[nextX][nextY] == 0)
            {
                game.ghost2.x = nextX;
                game.ghost2.y = nextY;
            }

            game.deliveryPatrolIndex =
                (game.deliveryPatrolIndex + 1) % 8;
        }

        if (game.difficulty == 3)
        {
            int patrol[4][2];

            int count =
                getAvailablePatrolPoints(
                    game.maze,
                    game.packageX,
                    game.packageY,
                    patrol);

            if (count > 0)
            {
                int index =
                    game.deliveryPatrolIndex % count;

                game.ghost3.x =
                    patrol[index][0];

                game.ghost3.y =
                    patrol[index][1];
            }
        }
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
            if (game.difficulty == 3)
            {
                game.ghost3.x =
                    game.packageX - 1;

                game.ghost3.y =
                    game.packageY;
            }
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
