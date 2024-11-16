#pragma once

#include "piece.h"

enum MoveType {
    Peaceful,
    Capture,
    Promotion,
};

struct move {
    Colour colour;
    Piece piece;
    int from;
    int to;

};
