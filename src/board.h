#pragma once

#include "piece.h"

#include <cstdint>
#include <map>
#include <iostream>
#include "utils.h"

using Bitboard = uint64_t;

class Board{
public:
    void init();
    bool pieceAtIndex(int index) const;
    friend std::ostream& operator << (std::ostream &os, const Board &b);
private:
    std::map<std::pair<enum Colour, enum Piece>, Bitboard> bitboards;
    std::string toString() const;
    std::pair<Colour, Piece> pieceAt(int index) const;
};
