#include "game.h"
#include "bitboards.h"
#include <iostream>

void Game::init() {
    board.init();
    turn = White;
}

bool Game::moveValid(struct move move) {
    if (move.colour != turn) {
        return false;
    }

    // Checks if there is the correct piece in the position of move.from
    if (!(board.bitboards[std::make_pair(move.colour, move.piece)] & move.from)) {
        return false;
    }

    std::pair<Colour, Piece> piece = board.pieceAt(move.to);

    if (move.piece == King) {
        Bitboard validPositions = nortOne(move.from) | noEaOne(move.from) | eastOne(move.from) | soEaOne(move.from) | soutOne(move.from) | soWeOne(move.from) |
                westOne(move.from) | noWeOne(move.from);

        // Checks that the to square is one of the valid move positions
        if (!(move.to & validPositions)) {
            return false;
        }

        if (move.type == Peaceful && piece.second != NullPiece) {
            return false;
        } else if (move.type == Capture && (piece.second == NullPiece or piece.first == move.colour)) {
            return false;
        }
    } else if (move.piece == Pawn) {
        if (move.type == Peaceful) {
            if (!(move.to & board.empty)) {
                // Target square not empty
                return false;
            }

            if ((move.colour == White ? move.from << 16 : move.from >> 16) == move.to) {
                // Checks if it is either on the second or seventh rank if it's a two square push
                if (!(move.from & (move.colour == Black ? move.from & 0xFFULL << 48 : 0xFF00))) {
                    return false;
                }
            } else if ((move.colour == White ? move.from << 8 : move.from >> 8) != move.to) {
                // Pawn can only move 1 or 2 squares forward
                return false;
            }
        } else if (move.type == Capture) {
            // Can only capture diagonally
            Bitboard validPositions = move.colour == White ? noWeOne(move.from) & noEaOne(move.from) : soWeOne(move.from) | soEaOne(move.from);
            if (!(move.to & validPositions)) {
                return false;
            }

            // There should be an opposite coloured piece on the target square
            if (piece.first == move.colour || piece.first == NullColour) {
                return false;
            }

        } else if (move.type == Promotion) {
            // Pawn can only move 1 or 2 squares forward
            if ((move.colour == White ? move.from << 8 : move.from >> 8) != move.to) {
                return false;
            }

            // Must be moving onto the final rank
            if (!(move.to & (move.colour == White ? 0xFFULL << 56 : 0xFF))) {
                return false;
            }

            if (!(move.to & board.empty)) {
                // Target square not empty
                return false;
            }
        } else {
            return false;
        }
    } else if (move.piece == Knight) {
        // Knight can move two squares in one direction and one in the other
        Bitboard validPositions = nortOne(noEaOne(move.from)) | eastOne(noEaOne(move.from)) | eastOne(soEaOne(move.from)) | soutOne(
                soEaOne(move.from)) | soutOne(soWeOne(move.from)) | westOne(soWeOne(move.from)) | westOne(noWeOne(move.from)) | nortOne(noWeOne(move.from));
        if (!(move.to & validPositions)) {
            return false;
        }

        // If move is peaceful then target square should be empty
        if (move.type == Peaceful && !(move.to & board.empty)) {
            return false;
        }

        // If move is a capture target square should be occupied by an opposite coloured piece
        if (move.type == Capture && (piece.first == move.colour || piece.first == NullColour)) {
            return false;
        }
    } else if (move.piece == Rook) {
        Bitboard between = exploreStraight(move.from, move.to);

        // Invalid path between the two points, not a straight line
        if (between == 0) {
            return false;
        }

        if (move.type == Peaceful) {
            // There should be no pieces along the path
            if (((between ^ move.to) & board.empty) != (between ^ move.to)) {
                return false;
            }
        } else if (move.type == Capture) {
            // There should be no pieces in between the two pieces
            if (((between ^ (move.to & move.from)) & board.empty) != (between ^ (move.to & move.from))) {
                return false;
            }

            // An opposite coloured piece should be occupying the target square
            if (piece.first == move.colour || piece.first == NullColour) {
                return false;
            }

        } else {
            return false;
        }

    } else {
            return false;
    }

    return true;
}

bool Game::makeMove(struct move move) {
    if (!moveValid(move)) {
        return false;
    }

    Bitboard pieces = board.bitboards[std::make_pair(move.colour, move.piece)];

    if (move.type == Peaceful) {
        board.bitboards[std::make_pair(move.colour, move.piece)] ^= move.from;
        board.bitboards[std::make_pair(move.colour, move.piece)] |= move.to;

        board.empty ^= move.from;
        board.empty |= move.to;
    }

    turn = turn == Black ? White : Black;
    return true;
}

void Game::printBoard() {
    std::cout << board;
}

struct move Game::parseMove(std::string move) {
    Bitboard to;
    if (move.length() == 2) {
        try {
            to = getSquare(move);
        } catch (std::string e) {
            throw std::invalid_argument("Square could not be parsed");
        }

        Bitboard from;

        if (turn == White) {
            if (board.occupied(soutOne(to))) {
                from = soutOne(to);
            } else {
                from = soutOne(soutOne(to));
            }
        } else {
            if (board.occupied(nortOne(to))) {
                from = nortOne(to);
            } else {
                from = nortOne(nortOne(to));
            }
        }

        return {turn, Pawn, from, to, Peaceful};
    }

    throw std::invalid_argument("Move could not be parsed");
}
