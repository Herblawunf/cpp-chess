#pragma once

#include "game.h"
#include "move.h"
#include <iostream>

class TwoPlayerGame {
public:
    Game game;
    void init();
    void startGame();
};
