#pragma once

#include "board.h"
#include "move.h"

class Game {
public:
    void init();
    bool makeMove(struct move move);
    void printBoard();
private:
    Board board;
    bool moveValid(struct move move);
    Colour turn;
};
