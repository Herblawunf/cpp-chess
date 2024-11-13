#include "utils.h"

int getSquareIndex(std::string square) {
    int col = int(square[1]) - 48;

    switch(tolower(square[0])) {
        case 'a':
            return col - 1;
        case 'b':
            return 7 + col;
        case 'c':
            return 15 + col;
        case 'd':
            return 23 + col;
        case 'e':
            return 31 + col;
        case 'f':
            return 39 + col;
        case 'g':
            return 47 + col;
        case 'h':
            return 55 + col;
        default:
            throw std::invalid_argument("Invalid square");
    }
}
