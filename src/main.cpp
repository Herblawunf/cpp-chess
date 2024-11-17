#include "board.h"
#include "game.h"
#include "utils.h"
#include <iostream>

using namespace std;
int main() {
    cout << "Program starting..." << endl;

    Game game;
    game.init();

    game.printBoard();

    return 0;
}