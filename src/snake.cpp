#include "snake.h"
#include <cmath>

Snake::Snake(): nextDirection(RIGHT){
    body.push_back({3, 9});
    body.push_front({3, 10});
}

int Snake::GetCurDir() {
    pii firPos = body.front();
    auto iter = body.begin();
    iter++;
    pii secPos = *iter;
    if (firPos.first == secPos.first && firPos.second > secPos.second) {
        return RIGHT;
    }
    else if (firPos.first == secPos.first && firPos.second < secPos.second) {
        return LEFT;
    }
    else if (firPos.first > secPos.first && firPos.second == secPos.second) {
        return DOWN;
    }
    else {
        return UP;
    }
}
pii Snake::GetNextPos() {
    pii nextPos = body.front();
    switch (nextDirection)
    {
    case UP:
        nextPos.first--;
        break;
    case RIGHT:
        nextPos.second++;
        break;
    case DOWN:
        nextPos.first++;
        break;
    case LEFT:
        nextPos.second--;
        break;
    default:
        break;
    }
    return nextPos;
}

int Snake::Advance() {
    pii nextPos = GetNextPos();
    body.push_front(nextPos);
    body.pop_back();
    return 0;
}

int Snake::EatFood(Food food) {
    body.push_front(food.GetPos());
    return 0;
}

int Snake::Turn(int nextDir) {
    int curDir = GetCurDir();
    if (abs(curDir - nextDir) == 2) {
        return nextDirection;
    }
    return nextDirection = nextDir;
}