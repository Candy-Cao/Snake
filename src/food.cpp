#include "food.h"
#include <stdlib.h>
#include <time.h>

Food::Food() {
    time_t t;
    time(&t);
    srand((unsigned)t);
    pos.first = rand() % 20 + 1;
    pos.second = rand() % 20 + 1;
}

void Food::Fresh(pii p) {
    pos = p;
}