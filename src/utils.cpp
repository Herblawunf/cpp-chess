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

std::string getPieceCharacter(std::pair<Colour, Piece> p) {
    Colour colour = p.first;
    Piece piece = p.second;

    if (colour == White) {
        switch (piece) {
            case Pawn:
                return "\u2659"; // ♙
            case Knight:
                return "\u2658"; // ♘
            case Bishop:
                return "\u2657"; // ♗
            case Rook:
                return "\u2656"; // ♖
            case Queen:
                return "\u2655"; // ♕
            case King:
                return "\u2654"; // ♔
            default:
                throw std::invalid_argument("Invalid piece");
        }
    } else if (colour == Black) {
        switch (piece) {
            case Pawn:
                return "\u265F"; // ♟
            case Knight:
                return "\u265E"; // ♞
            case Bishop:
                return "\u265D"; // ♝
            case Rook:
                return "\u265C"; // ♜
            case Queen:
                return "\u265B"; // ♛
            case King:
                return "\u265A"; // ♚
            default:
                throw std::invalid_argument("Invalid piece");
        }
    }
    throw std::invalid_argument("Invalid colour");
}

