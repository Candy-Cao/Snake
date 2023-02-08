#include "ui.h"

LocalUi::LocalUi() {
    SetStart(START_ROW, START_COL);

    setupterm(NULL, fileno(stdout), NULL);
    cursor = tigetstr("cup");
    clear = tigetstr("clear");
    setbuf(stdout, NULL);
	setbuf(stderr, NULL);
}

int LocalUi::OutPut(Frame &frame) {
    pii pos;
    Clear();
    SetCursor(START_ROW, START_COL);
    for (int j = 0; j < MAP_SIZE; j++) {
        cout << "--";
    }
    SetCursor(START_ROW + 1, START_COL);
    for (int i = 1; i < MAP_SIZE - 1; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (j == 0) {
                cout << "||";
                continue;
            }
            if (j == MAP_SIZE - 1) {
                cout << "||";
                continue;
            }
            switch (frame[i][j]) {
            case SPACE_NUM:
                cout << "  ";
                break;
            case BAR_NUM:
                cout << "II";
                break;
            case FOOD_NUM:
                cout << "()";
                pos = {i, j};
                break;
            case BODY_NUM:
                cout << "[]";
                break;
            case HEAD_NUM:
                cout << "88";
                break;
            default:
                cerr << "unkown unit!" << endl;
                return -1;
            }
        }
        SetCursor(START_ROW + 1 + i, START_COL);
    }
    for (int j = 0; j < MAP_SIZE; j++) {
        cout << "--";
    }
    cout << endl << "APP VERSION(" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << ")" << endl;
    return 0;
}

int LocalUi::SetCursor(int x, int y) {
    char *esc_sequence;
    SetStart(x, y);
    esc_sequence = tparm(cursor, GetStart().first, GetStart().second);
    int ret = putp(esc_sequence);
    if (ret != 0) {
        cerr << "set cursor failed!" << endl;
        return -1;
    }
    return 0;
}

int LocalUi::Clear() {
    int ret = putp(clear);
    if (ret != 0) {
        cerr << "clear the screen faild!" << endl;
    }
    return ret;
}

