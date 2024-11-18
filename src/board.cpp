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

    empty = 0x0000FFFFFFFF0000ULL;
}

// Checks if there is a piece at an index from 0 to 63 inclusive
// a1 -> 0, a2 -> 1, ... , b1 -> 8, ... h8 -> 63
bool Board::pieceAtIndex(Bitboard position) const {
    for (const auto& [piece, bitboard] : bitboards) {
        if (bitboard & position) {
            return true;
        }
    }
    return false;
}

std::pair<Colour, Piece> Board::pieceAt(Bitboard position) const {
    for (const auto& [piece, bitboard] : bitboards) {
        if (bitboard & position) {
            return piece;
        }
    }
    return std::make_pair(NullColour, NullPiece);
}

std::ostream& operator << (std::ostream &os, const Board &b) {
    return (os << b.toString());
}

std::string Board::toString() const {
    std::string ret = "  A B C D E F G H  \n";

    for (int row = 7; row >= 0; row--) {
        ret.append(std::to_string(row + 1) + " ");
        for (int col = 0; col < 8; col++) {
            int index = row * 8 + col;

            if (this->pieceAtIndex(1ULL << index)) {
                ret.append(getPieceCharacter(this->pieceAt(1ULL << index)));
            } else {
                ret.append(".");
            }
            ret.append(" ");
        }
        ret.append(std::to_string(row) + "\n");
    }

    ret.append("  A B C D E F G H  \n");

    return ret;
}
