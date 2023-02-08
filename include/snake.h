#ifndef SNAKE_H
#define SNAKE_H
#include "define.h"
#include "food.h"
#include <list>

class Snake {
public:
    Snake();
    ~Snake() {}
    int GetCurDir();
    pii GetNextPos();
    int Advance();
    int EatFood(Food food);
    int Turn(int nextDir);
    const list<pii> &GetBody() {return body;}
    pii GetHead() {return body.front();}

private:
    list<pii> body;
    int nextDirection;
};

#endif