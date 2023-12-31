#include "user.h"

LocalUser::LocalUser() {
    tcgetattr(fileno(stdin), &cur_terms);
    init_terms = cur_terms;
    cur_terms.c_lflag &= ~ICANON;
    cur_terms.c_lflag &= ~ECHO;
    cur_terms.c_cc[VMIN] = 1;
    cur_terms.c_cc[VTIME] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &cur_terms);

    SetStart(START_ROW, START_COL);
    setupterm(NULL, fileno(stdout), NULL);
    cursor = tigetstr("cup");
    clear = tigetstr("clear");
    setbuf(stdout, NULL);
	setbuf(stderr, NULL);
}

LocalUser::~LocalUser() {
    tcsetattr(fileno(stdin), TCSANOW, &init_terms);
}

char LocalUser::kbhit() {
    char ret;
    read(fileno(stdin), &ret, 1);
    return ret;
}

char LocalUser::Input() {
    return kbhit();
}

int LocalUser::OutPut(Frame &frame) {
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
    cout << endl << "APP VERSION(" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << ")" << "developer--candy" << endl;
    cout << "操作方式:A--left, S--down, D--right, W--up, b--begin/break, q--quit" << endl;
    return 0;
}
int LocalUser::SetCursor(int x, int y) {
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
int LocalUser::Clear() {
    int ret = putp(clear);
    if (ret != 0) {
        cerr << "clear the screen faild!" << endl;
    }
    return ret;
}