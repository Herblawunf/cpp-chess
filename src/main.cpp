#include "board.h"
#include "game.h"
#include "utils.h"
#include "move.h"
#include "twoPlayerGame.h"
#include <iostream>

using namespace std;
int main() {
    cout << "Program starting..." << endl;

    cout << exploreStraight(0b100000000, 0b1000000000000000LL) << endl;

    TwoPlayerGame game;

    game.init();

    game.startGame();

    return 0;
}