#pragma once

#include <string>
#include <stdexcept>

#include "piece.h"

int getSquareIndex(std::string square);

std::string getPieceCharacter(std::pair<Colour, Piece> p);
