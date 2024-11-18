#pragma once

#include "board.h"
#include "move.h"

class Game {
public:
    void init();
    bool makeMove(struct move move);
    void printBoard();
    bool moveValid(struct move move);
    struct move parseMove(std::string move);
private:
    Board board;
    Colour turn;
};
