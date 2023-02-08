#include "user.h"

LocalUser::LocalUser() {
    tcgetattr(fileno(stdin), &cur_terms);
    init_terms = cur_terms;
    cur_terms.c_lflag &= ~ICANON;
    cur_terms.c_lflag &= ~ECHO;
    cur_terms.c_cc[VMIN] = 1;
    cur_terms.c_cc[VTIME] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &cur_terms);
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