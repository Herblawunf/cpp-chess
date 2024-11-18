#pragma once

#include <cstdint>

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
