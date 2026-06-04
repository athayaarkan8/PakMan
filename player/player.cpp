#include "player.h"

Player::Player(int startX, int startY)
{
    x = startX;
    y = startY;

    rewindEnergy = 3;
}

void Player::move(char input, int maze[SIZE][SIZE])
{
    int newX = x;
    int newY = y;

    switch(input)
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

    if(newX >= 0 &&
       newY >= 0 &&
       newX < SIZE &&
       newY < SIZE &&
       maze[newX][newY] == 0)
    {
        history.push({x, y});

        x = newX;
        y = newY;
    }
}

void Player::rewind()
{
    if(history.isEmpty())
    {
        return;
    }

    if(rewindEnergy <= 0)
    {
        return;
    }

    Position previous = history.pop();

    x = previous.x;
    y = previous.y;

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
