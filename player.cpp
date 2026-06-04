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
    if(rewindEnergy <= 0)
    {
        return;
    }

    Position previous = {x, y};

    for(int i = 0; i < 5; i++)
    {
        if(history.isEmpty())
        {
            break;
        }

        previous = history.pop();
    }

    x = previous.x;
    y = previous.y;

    rewindEnergy--;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

int Player::getEnergy()
{
    return rewindEnergy;
}
