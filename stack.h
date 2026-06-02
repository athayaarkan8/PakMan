#ifndef STACK_H
#define STACK_H

struct Position
{
    int x;
    int y;
};

class Stack
{
private:
    Position data[100];
    int top;

public:
    Stack();

    void push(Position p);

    Position pop();

    bool isEmpty();
};

#endif