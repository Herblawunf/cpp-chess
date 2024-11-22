#pragma once

#include <cstdint>
#include <iostream>

using Bitboard = uint64_t;

Bitboard soutOne (Bitboard b);
Bitboard nortOne (Bitboard b);
Bitboard eastOne (Bitboard b);
Bitboard noEaOne (Bitboard b);
Bitboard soEaOne (Bitboard b);
Bitboard westOne (Bitboard b);
Bitboard soWeOne (Bitboard b);
Bitboard noWeOne (Bitboard b);

Bitboard indexBoard(int index);

Bitboard exploreStraight(Bitboard from, Bitboard to);

Bitboard exploreDiagonal(Bitboard from, Bitboard to);

Bitboard rankMask(int sq);

Bitboard fileMask(int sq);

Bitboard diagonalMask(int sq);

Bitboard antiDiagMask(int sq);

Bitboard knightMask(int sq);

std::vector<Bitboard> splitBoard(Bitboard b);

int fileIndex(Bitboard b);
