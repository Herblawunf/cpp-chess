#include "board.h"
#include "game.h"
#include "utils.h"
#include "move.h"
#include "twoPlayerGame.h"
#include <iostream>

using namespace std;
int main() {
    cout << "Program starting..." << endl;



    TwoPlayerGame game;

    game.init();

    game.startGame();

    return 0;
}