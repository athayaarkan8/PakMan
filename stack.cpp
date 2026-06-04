#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack()
{
    top = -1;
}

void Stack::push(Position p)
{
    if(top < 99)
    {
        top++;
        data[top] = p;
    }
}

Position Stack::pop()
{
    Position emptyPos = {-1, -1};

    if(isEmpty())
    {
        return emptyPos;
    }

    Position temp = data[top];
    top--;

    return temp;
}

bool Stack::isEmpty()
{
    return top == -1;
}