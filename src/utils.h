#pragma once

#include <string>
#include <stdexcept>

#include "piece.h"
#include "move.h"
#include "bitboards.h"

#define opposite(colour) colour == White ? Black : White

Bitboard getSquare(std::string square);

std::string getPieceCharacter(std::pair<Colour, Piece> p);
