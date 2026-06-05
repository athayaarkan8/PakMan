#include "player.h"

Player::Player(int startX, int startY)
{
    x = startX;
    y = startY;

    rewindEnergy = 1;
    stepCounter = 0;
    justRewinded = false;
}

void Player::move(char input, int maze[SIZE][SIZE])
{
    justRewinded = false;

    int newX = x;
    int newY = y;

    switch (input)
    {
    case 'W':
    case 'w':
        newX--;
        break;

    case 'S':
    case 's':
        newX++;
        break;

    case 'A':
    case 'a':
        newY--;
        break;

    case 'D':
    case 'd':
        newY++;
        break;

    default:
        return;
    }

    if (newX >= 0 &&
        newY >= 0 &&
        newX < SIZE &&
        newY < SIZE &&
        maze[newX][newY] == 0)
    {
        history.push({x, y});

        x = newX;
        y = newY;
        stepCounter++;

        if (stepCounter >= 13)
        {
            stepCounter = 0;

            if (rewindEnergy < 3)
            {
                rewindEnergy++;
            }
        }
    }
}

void Player::rewind()
{

    if (rewindEnergy <= 0)
    {
        return;
    }

    if (history.isEmpty())
    {
        return;
    }
    justRewinded = true;

    Position target;

    int steps = 3;

    while (steps > 0 && !history.isEmpty())
    {
        target = history.pop();
        steps--;
    }

    x = target.x;
    y = target.y;

    rewindEnergy--;
}

int Player::getX() const
{
    return x;
}

int Player::getY() const
{
    return y;
}

int Player::getEnergy() const
{
    return rewindEnergy;
}

int Player::getStepCounter() const
{
    return stepCounter;
}

bool Player::hasJustRewinded() const
{
    return justRewinded;
}

void Player::resetRewindFlag()
{
    justRewinded = false;
}
