#include "game.h"

void Game::init() {
    board.init();
    turn = White;
}

bool Game::moveValid(struct move move) {
    if (move.colour != turn) {
        return false;
    }

    return true;
}

bool Game::makeMove(struct move move) {
    if (!moveValid(move)) {
        return false;
    }

    return true;
}

void Game::printBoard() {
    std::cout << board;
}
