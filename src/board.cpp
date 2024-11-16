//
// Created by Dylan Beharall on 13/11/2024.
//

#include "board.h"

void Board::init() {
    bitboards[std::make_pair(White, Pawn)] = 0b11111111ULL << 8;
    bitboards[std::make_pair(Black, Pawn)] = 0b11111111ULL << 48;

    bitboards[std::make_pair(White, Knight)] = 0b01000010;
    bitboards[std::make_pair(Black, Knight)] = 0b01000010ULL << 56;

    bitboards[std::make_pair(White, Bishop)] = 0b00100100;
    bitboards[std::make_pair(Black, Bishop)] = 0b00100100ULL << 56;

    bitboards[std::make_pair(White, Rook)] = 0b10000001;
    bitboards[std::make_pair(Black, Rook)] = 0b10000001ULL << 56;

    bitboards[std::make_pair(White, Queen)] = 0b1000;
    bitboards[std::make_pair(Black, Queen)] = 0b1000ULL << 56;

    bitboards[std::make_pair(White, King)] = 0b10000;
    bitboards[std::make_pair(Black, King)] = 0b10000ULL << 56;
}

// Checks if there is a piece at an index from 0 to 63 inclusive
// a1 -> 0, a2 -> 1, ... , b1 -> 8, ... h8 -> 63
bool Board::pieceAtIndex(int index) {
    if (index < 0 || index > 63) {
        return false;
    }

    uint64_t mask = 1ULL << index;

    for (const auto& [piece, bitboard] : bitboards) {
        if (bitboard & mask) {
            return true;
        }
    }
    return false;
}
