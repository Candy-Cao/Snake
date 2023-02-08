#include "Game.h"

int main() {
    Game game;
    int ret = game.Run();
    if (ret == 1) {
        cerr << "Perfect!!!" << endl;
    }
    return 0;
}