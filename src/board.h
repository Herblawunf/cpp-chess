#pragma once

#include "piece.h"

#include <cstdint>
#include <map>
#include <iostream>
#include "utils.h"
#include "bitboards.h"

class Board{
public:
    void init();
    bool pieceAtIndex(Bitboard position) const;
    friend std::ostream& operator << (std::ostream &os, const Board &b);
    std::pair<Colour, Piece> pieceAt(Bitboard position) const;
    std::map<std::pair<enum Colour, enum Piece>, Bitboard> bitboards;
    Bitboard empty;
private:
    std::string toString() const;
};
