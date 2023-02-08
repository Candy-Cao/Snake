#ifndef USER_H
#define USER_H

#include <unistd.h>
#include <termios.h>
#include <ncurses.h>
#include <term.h>

class User {
public:
    User() = default;
    User(int id): userId(id) {};
    ~User() = default;
    virtual char Input() = 0;
    void SetUserId(int id) {userId = id;}
private:
    int userId = 0;
};

class LocalUser: public User {
public:
    LocalUser();
    ~LocalUser();
    char kbhit();
    char Input();
private:
    struct termios cur_terms, init_terms;
};



#endif