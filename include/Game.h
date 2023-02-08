#ifndef GAME_H
#define GAME_H
#include "food.h"
#include "snake.h"
#include "plat.h"
#include "ui.h"
#include "user.h"
#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/util.h>
#include <thread>

class Game {
public:
    Game();
    Game(vector<vector<int>> &vec): plat(vec) {}
    const Frame &GetCurFrame();
    int FreshFood();
    int Tick();
    int Run();
private:
    bool startFlag;
    Food food;
    Snake snake;
    Plat plat;
    Frame frame;
    LocalUser user;
    LocalUi ui;
    vector<pii> spaceVec;
	struct timeval tv;
	struct event_base *base;
    struct event timeout;
    mutex tickMutex;
};

static void TimeOutCb(evutil_socket_t fd, short event, void *arg);

#endif