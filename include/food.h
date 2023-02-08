#ifndef FOOD_H
#define FOOD_H

#include "plat.h"
#include <define.h>


class Food {
public:
    Food();
    Food(int x, int y): pos(x, y) {};
    Food(pii &p): pos(p) {}
    const pii &GetPos() const {return pos;}
    bool SetEatenFlag(bool flag) {return eaten = flag;}
    bool IsEaten() {return eaten;}
    ~Food() {}
    void Fresh(pii p);
private:
    pii pos;
    bool eaten = false;
};

#endif