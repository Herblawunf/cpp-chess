#include "board.h"
#include "game.h"
#include "utils.h"
#include "move.h"
#include <iostream>

using namespace std;
int main() {
    cout << "Program starting..." << endl;

    Game game;
    game.init();

    game.printBoard();

    struct move move = game.parseMove("e4");

    game.makeMove(move);

    game.printBoard();

    struct move move2 = {Black, Pawn, 1ULL << 48, 1ULL << 40, Peaceful};

    game.makeMove(move2);

    game.printBoard();

    return 0;
}