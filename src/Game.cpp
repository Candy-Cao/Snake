#include "Game.h"
#include <functional>

Game::Game(): startFlag(false), perfectFlag(false), gameOverFlag(false) {
    base = event_base_new();
    event_assign(&timeout, base, -1, EV_PERSIST, TimeOutCb, (void*)this);
    evutil_timerclear(&tv);
	tv.tv_sec = 1;
	event_add(&timeout, &tv);
    GetCurFrame();
}
Game::~Game() {
    event_base_free(base);
}
const Frame &Game::GetCurFrame() {
    frame = plat.ToFrame();
    for(auto &pos: snake.GetBody()) {
        frame[pos.first][pos.second] = BODY_NUM;
    }
    auto po = snake.GetHead();
    frame[po.first][po.second] = HEAD_NUM;
    po = food.GetPos();
    frame[po.first][po.second] = FOOD_NUM;
    return frame;
}
/*return value: 1 show that game over perfect*/
int Game::FreshFood() {
    spaceVec.clear();
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (frame[i][j] == 0) {
                spaceVec.emplace_back(i, j);
            }
        }
    }
    if (spaceVec.size() == 0) {
        return 1;
    }
    int index = rand() % spaceVec.size();
    food.Fresh(spaceVec[index]);
    food.SetEatenFlag(false);
    return 0;
}
/* return value: 0-succeed, -1-fail, 1-game over*/
int Game::Tick() {
    lock_guard<mutex> lock(tickMutex);
    int ret = 0;
    pii nextPos = snake.GetNextPos();
    switch (frame[nextPos.first][nextPos.second]) {
    case BAR_NUM:
        cerr << "GAME_OVER!!!" << endl;
        return -1;
    
    case FOOD_NUM:
        snake.EatFood(food);
        ret = FreshFood();
        break;

    case BODY_NUM:
        cerr << "GAME_OVER!!!" << endl;
        return -1;

    default:
        ret = snake.Advance();
        break;
    }
    GetCurFrame();
    ui.OutPut(frame);
    if (ret == 1) {
        perfectFlag = true;
    }
    return ret;
}

int Game::Run() {
    int ret = 0;
    ui.OutPut(frame);
    thread user_control([this](){
        char ch;
        while (!gameOverFlag && (ch = user.Input()) != 'q') {
            switch (ch) {
            case 'a':
                snake.Turn(LEFT);
                break;
            case 'w':
                snake.Turn(UP);
                break;
            case 'd':
                snake.Turn(RIGHT);
                break;
            case 's':
                snake.Turn(DOWN);
                break;
            case 'b':
                GameBreak();
                break;
            }
            if (!startFlag) {
                continue;
            }
            int ret = Tick();
            if (ret != 0) {
                evtimer_del(&timeout);
                event_base_loopbreak(base);
                break;
            }
            evtimer_del(&timeout);
            evtimer_add(&timeout, &tv);
        }
        evtimer_del(&timeout);
        event_base_loopbreak(base);
        return ;
    });

	event_base_dispatch(base);
    user_control.join();
    return perfectFlag ? 1 : -1;
}

int Game::GameOver() {
    evtimer_del(&timeout);
    event_base_loopbreak(base);
    gameOverFlag = true;
    user.~LocalUser();
    exit(-1);
}

int Game::GameBreak() {
    startFlag = !startFlag;
    return 0;
}

static void TimeOutCb(evutil_socket_t fd, short event, void *arg) {
    (void)fd;
    (void)event;
    Game* game = (Game*)arg;
    if (!game->GetStartFlag()) {
        return ;
    }
    int ret = game->Tick();
    if (ret != 0) {
        game->GameOver();
    }
}