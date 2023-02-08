#include "food.h"
#include <iostream>

int main() {
    Food f;
    Food g(2, 5);
    cout << f.GetPos().first << "," << f.GetPos().second << endl;
    cout << g.GetPos().first << "," << g.GetPos().second << endl;
    return 0;
}