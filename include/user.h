#ifndef USER_H
#define USER_H

#include <unistd.h>
#include <termios.h>
#include <ncurses.h>
#include <term.h>
#include <iostream>
#include "define.h"
#include "food.h"
#include "snake.h"
#include "plat.h"

class User {
public:
    User() = default;
    User(int id): userId(id) {};
    ~User() = default;
    virtual int Clear() = 0; //清除所有输出
    virtual char Input() = 0;
    virtual int OutPut(Frame &frame) = 0;
    void SetStart(int x, int y) {start = {x, y};}
    const pii &GetStart() const {return start;}
    void SetUserId(int id) {userId = id;}
private:
    int userId = 0;
    pii start;
};

class LocalUser: public User {
public:
    LocalUser();
    ~LocalUser();
    char kbhit();
    char Input();
    int OutPut(Frame &frame);
    int SetCursor(int x, int y);
    int Clear();
private:
    struct termios cur_terms, init_terms;
    char *cursor, *clear;
};

class WebUser: public User {
public:

private:

};



#endif