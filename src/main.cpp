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

    struct move move = {White, Knight, 1 << 6, 1 << 21, Peaceful};

    cout << game.makeMove(move) << endl;

    game.printBoard();

    struct move move2 = {Black, Pawn, 1ULL << 48, 1ULL << 40, Peaceful};

    cout << game.makeMove(move2) << endl;

    game.printBoard();

    return 0;
}