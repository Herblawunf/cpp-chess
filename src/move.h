#pragma once

#include "piece.h"
#include "bitboards.h"

enum MoveType {
    Peaceful,
    Capture,
    Promotion,
    Castle,
    PromotionCapture,
};

struct move {
    Colour colour;
    Piece piece;
    Bitboard from;
    Bitboard to;
    MoveType type;
    Piece promotionPiece;
};
