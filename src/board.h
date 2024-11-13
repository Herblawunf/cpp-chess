#pragma once

#include "piece.h"

#include <cstdint>
#include <map>

using Bitboard = uint64_t;

class Board{
public:
    void init();
    bool pieceAtIndex(int index);
private:
    std::map<std::pair<enum Colour, enum Piece>, Bitboard> bitboards;
};
