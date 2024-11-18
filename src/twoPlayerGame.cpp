#include "twoPlayerGame.h"

void TwoPlayerGame::init() {
    game.init();
}

void TwoPlayerGame::startGame() {
    game.printBoard();
    while (true) {
        std::cout << "Enter move: (" << (game.turn == White ? "White)" : "Black)") << std::endl;

        struct move move;
        std::string s;

        while (true) {
            std::cin >> s;

            try {
                move = game.parseMove(s);

                if (!game.makeMove(move)) {
                    std::cout << "Impossible move, try again" << std::endl;
                    continue;
                } else {
                    break;
                }

                break;
            } catch (std::invalid_argument e) {
                std::cout << "Move could not be parsed, try again" << std::endl;
            }
        }

        game.printBoard();
    }
}
