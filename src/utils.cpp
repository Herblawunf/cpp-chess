#include "utils.h"

Bitboard getSquare(std::string square) {
    int col = int(square[0]) - int('a');

    switch(square[1]) {
        case '1':
            return 1ULL << col;
        case '2':
            return 1ULL << (8 + col);
        case '3':
            return 1ULL << (16 + col);
        case '4':
            return 1ULL << (24 + col);
        case '5':
            return 1ULL << (32 + col);
        case '6':
            return 1ULL << (40 + col);
        case '7':
            return 1ULL << (48 + col);
        case '8':
            return 1ULL << (56 + col);
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
