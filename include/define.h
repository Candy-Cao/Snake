#ifndef DEFINE_H
#define DEFINE_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include <mutex>
using namespace std;

#define MAP_SIZE 22
#define HEAD_NUM 3
#define BODY_NUM 2
#define SPACE_NUM 0
#define BAR_NUM 1
#define FOOD_NUM 4
#define START_ROW 5
#define START_COL 10
typedef pair<int, int> pii;
typedef array<array<int, MAP_SIZE>, MAP_SIZE> Frame;
typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    DIRRECTION_BUTT
} Direction;
#endif
