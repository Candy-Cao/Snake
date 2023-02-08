#ifndef UI_H
#define UI_H

#include "food.h"
#include "snake.h"
#include "plat.h"
#include <term.h>
#include <iostream>
class Ui {
public:
    Ui() = default;
    ~Ui() = default;
    virtual int OutPut(Frame &frame) = 0;
    virtual int Clear() = 0;
    void SetStart(int x, int y) {start = {x, y};}
    const pii &GetStart() const {return start;}
private:
    pii start;
};

class LocalUi: public Ui {
public:
    LocalUi();
    ~LocalUi() = default;
    int OutPut(Frame &frame);
    int SetCursor(int x, int y);
    int Clear();
private:
    char *cursor, *clear;
};

#endif