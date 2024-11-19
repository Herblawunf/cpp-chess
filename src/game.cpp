#include "game.h"
#include "bitboards.h"
#include <iostream>

void Game::init() {
    board.init();
    turn = White;

    whiteKingSideCastle = true;
    whiteQueenSideCastle = true;
    blackKingSideCastle = true;
    blackQueenSideCastle = true;
}

bool Game::moveValid(struct move move) {
    if (move.colour != turn || move.to == move.from) {
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
        if (move.type != Castle && !(move.to & validPositions)) {
            return false;
        }

        if (move.type == Peaceful) {
            if (piece.second != NullPiece) {
                return false;
            }
        } else if (move.type == Capture) {
            if (piece.second == NullPiece or piece.first == move.colour) {
                return false;
            }
        } else if (move.type == Castle) {
            if (move.colour == White) {
                // The from square should be the starting king square
                if (move.from != 0b10000) {
                    return false;
                }

                if (move.to == 0b1000000) {
                    // Kingside castle
                    std::cout << (0b1100000 & board.empty) << std::endl;
                    if ((!whiteKingSideCastle) || (0b1100000 & board.empty) != 0b1100000) {
                        return false;
                    }
                } else if (move.to == 0b100) {
                    // Queenside castle
                    if ((!whiteQueenSideCastle) || (0b1110 & board.empty) != 0b1110) {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                // The from square should be the starting king square
                if (move.from != 0b10000ULL << 56) {
                    return false;
                }

                if (move.to == 0b1000000ULL << 56) {
                    // Kingside castle
                    if ((!blackKingSideCastle) || ((0b1100000ULL << 56) & board.empty) != (0b1100000ULL << 56)) {
                        return false;
                    }
                } else if (move.to == 0b100ULL << 56) {
                    // Queenside castle
                    if ((!blackQueenSideCastle) || ((0b1110ULL << 56) & board.empty) != (0b1110ULL << 56)) {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }

    } else if (move.piece == Pawn) {
        // Pawn must promote when moving to the final rank
        if (move.to & (move.colour == White ? 0xFF00000000000000 : 0xFF) && move.type != Promotion) {
            return false;
        }

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
            Bitboard validPositions = move.colour == White ? noWeOne(move.from) | noEaOne(move.from) : soWeOne(move.from) | soEaOne(move.from);
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
            if (((between ^ move.from) & board.empty) != (between ^ move.from)) {
                return false;
            }
        } else if (move.type == Capture) {
            // There should be no pieces in between the two pieces
            if (((between ^ (move.to | move.from)) & board.empty) != (between ^ (move.to | move.from))) {
                return false;
            }

            // An opposite coloured piece should be occupying the target square
            if (piece.first == move.colour || piece.first == NullColour) {
                return false;
            }

        } else {
            return false;
        }

    } else if (move.piece == Bishop) {
        Bitboard between = exploreDiagonal(move.from, move.to);

        // Invalid path between the two points, not a straight line
        if (between == 0) {
            return false;
        }

        if (move.type == Peaceful) {
            // There should be no pieces along the path
            if (((between ^ move.from) & board.empty) != (between ^ move.from)) {
                return false;
            }
        } else if (move.type == Capture) {
            // There should be no pieces in between the two pieces
            if (((between ^ (move.to | move.from)) & board.empty) != (between ^ (move.to | move.from))) {
                return false;
            }

            // An opposite coloured piece should be occupying the target square
            if (piece.first == move.colour || piece.first == NullColour) {
                return false;
            }

        }  else {
            return false;
        }

    } else if (move.piece == Queen) {
        Bitboard between = exploreStraight(move.from, move.to) | exploreDiagonal(move.from, move.to);

        // Invalid path between the two points, not a straight line
        if (between == 0) {
            return false;
        }

        if (move.type == Peaceful) {
            // There should be no pieces along the path
            if (((between ^ move.from) & board.empty) != (between ^ move.from)) {
                return false;
            }
        } else if (move.type == Capture) {
            // There should be no pieces in between the two pieces
            if (((between ^ (move.to | move.from)) & board.empty) != (between ^ (move.to | move.from))) {
                return false;
            }

            // An opposite coloured piece should be occupying the target square
            if (piece.first == move.colour || piece.first == NullColour) {
                return false;
            }

        }  else {
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

        board.empty ^= move.to;
        board.empty |= move.from;
    } else if (move.type == Capture) {
        board.bitboards[std::make_pair(move.colour, move.piece)] ^= move.from;
        board.bitboards[std::make_pair(move.colour, move.piece)] |= move.to;

        for (int p = Pawn; p <= King; p++) {
            if (board.bitboards[std::make_pair(opposite(move.colour), static_cast<Piece>(p))] & move.to) {
                board.bitboards[std::make_pair(opposite(move.colour), static_cast<Piece>(p))] ^= move.to;
                break;
            }
        }

        board.empty |= move.from;
    } else if (move.type == Castle) {
        Bitboard corner;
        Bitboard rookPos;
        Bitboard kingPos;

        if (move.to == 0b100) {
            corner = 1;
            rookPos = 0b1000;
            kingPos = 0b100;
        } else if (move.to == 0b1000000) {
            corner = 0b10000000;
            rookPos = 0b100000;
            kingPos = 0b1000000;
        } else if (move.to == 0b100ULL << 56) {
            corner = 1ULL << 56;
            rookPos = 0b1000ULL << 56;
            kingPos = 0b100ULL << 56;
        } else {
            corner = 0b10000000ULL << 56;
            rookPos = 0b100000ULL << 56;
            kingPos = 0b1000000ULL << 56;
        }

        if (move.colour == White) {
            whiteQueenSideCastle = false;
            whiteKingSideCastle = false;
        } else if (move.colour == Black) {
            blackQueenSideCastle = false;
            blackKingSideCastle = false;
        }

        board.bitboards[std::make_pair(move.colour, Rook)] ^= corner | rookPos;
        board.bitboards[std::make_pair(move.colour, King)] ^= move.from | kingPos;

        board.empty ^= move.from | rookPos | kingPos | corner;
    } else if (move.type == Promotion) {
        board.bitboards[std::make_pair(move.colour, Pawn)] ^= move.from;
        board.bitboards[std::make_pair(move.colour, move.promotionPiece)] |= move.to;

        board.empty ^= move.to;
        board.empty |= move.from;
    }

    // Logic for loss of castling right
    if (move.colour == White) {
        if (move.piece == King && move.from == 0b10000) {
            whiteQueenSideCastle = false;
            whiteKingSideCastle = false;
        }
        else if (move.piece == Rook && move.from == 1) {
            whiteQueenSideCastle = false;
        }
        else if (move.piece == Rook && move.from == 0b10000000) {
            whiteKingSideCastle = false;
        }
    } else if (move.colour == Black) {
        if (move.piece == King && move.from == 0b10000ULL << 56) {
            blackQueenSideCastle = false;
            blackKingSideCastle = false;
        }
        else if (move.piece == Rook && move.from == 1ULL << 56) {
            blackQueenSideCastle = false;
        }
        else if (move.piece == Rook && move.from == 0b10000000ULL << 56) {
            blackKingSideCastle = false;
        }
    }

    turn = turn == Black ? White : Black;
    return true;
}

void Game::printBoard() const {
    std::cout << board;
}

std::map<char, Piece> pieceMap{{'K', King}, {'Q', Queen}, {'R', Rook}, {'B', Bishop}, {'N', Knight}};

struct move Game::parseMove(std::string move) {
    if (move == "O-O") {
        // Kingside castle
        Bitboard from = turn == White ? 0b10000 : 0b10000ULL << 56;
        Bitboard to = turn == White ? 0b1000000 : 0b1000000ULL << 56;

        return {turn, King, from, to, Castle, NullPiece};
    } else if (move == "O-O-O") {
        Bitboard from = turn == White ? 0b10000 : 0b10000ULL << 56;
        Bitboard to = turn == White ? 0b100 : 0b100ULL << 56;

        return {turn, King, from, to, Castle, NullPiece};
    }

    Bitboard to;

    if (move.find('=') == std::string::npos) {
        try {
            to = getSquare(move.substr(move.length() - 2, 2));
        } catch (std::string e) {
            throw std::invalid_argument("Square could not be parsed");
        }
    }

    if (move.length() == 2) {
        // The case where the move is a peaceful pawn move

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

        return {turn, Pawn, from, to, Peaceful, NullPiece};
    } else if (move.length() == 3) {
        // The case where the move is a peaceful move with a non-pawn piece
        Piece piece = pieceMap[move[0]];
        Bitboard from;

        if (piece == Rook) {
            int square = __builtin_ctzll(to);
            Bitboard possibleFroms = rankMask(square) | fileMask(square);

            from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];

            if (from != (1 << __builtin_ctzll(from))) {
                // In this case there are multiple pieces on the same rank/file but only one possible move
                std::vector<Bitboard> split = splitBoard(from);
                struct move m;

                for (auto b : split) {
                    m = {turn, Rook, b, to, Peaceful, NullPiece};

                    if (moveValid(m)) {
                        return m;
                    }
                }
                return m;
            }

        } else if (piece == Bishop) {
            int square = __builtin_ctzll(to);
            Bitboard possibleFroms = diagonalMask(square) | antiDiagMask(square);

            from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];

            if (from != (1 << __builtin_ctzll(from))) {
                // In this case there are multiple pieces on the same diagonal but only one possible move
                std::vector<Bitboard> split = splitBoard(from);
                struct move m;

                for (auto b : split) {
                    m = {turn, Bishop, b, to, Peaceful, NullPiece};

                    if (moveValid(m)) {
                        return m;
                    }
                }
                return m;
            }
        } else if (piece == Queen) {
            int square = __builtin_ctzll(to);
            Bitboard possibleFroms = rankMask(square) | fileMask(square) | diagonalMask(square) | antiDiagMask(square);

            from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];

            if (from != (1 << __builtin_ctzll(from))) {
                // In this case there are multiple pieces on the same diagonal but only one possible move
                std::vector<Bitboard> split = splitBoard(from);
                struct move m;

                for (auto b : split) {
                    m = {turn, Queen, b, to, Peaceful, NullPiece};

                    if (moveValid(m)) {
                        return m;
                    }
                }
                return m;
            }
        } else if (piece == Knight) {
            int square = __builtin_ctzll(to);
            Bitboard possibleFroms = knightMask(square);

            from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];
        } else {
            from = 0;
        }

        return {turn, piece, from, to, Peaceful, NullPiece};
    } else if (move.length() == 4) {
        // In this case it is either a peaceful ambiguous move or a capture, or a promotion

        if (move.find('x') != std::string::npos) {
            // Capture case

            Piece piece = pieceMap.find(move[0]) != pieceMap.end() ? pieceMap[move[0]] : Pawn;
            Bitboard from;

            if (piece == Rook) {
                int square = __builtin_ctzll(to);
                Bitboard possibleFroms = rankMask(square) | fileMask(square);

                from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];
            } else if (piece == Bishop) {
                int square = __builtin_ctzll(to);
                Bitboard possibleFroms = diagonalMask(square) | antiDiagMask(square);

                from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];
            } else if (piece == Queen) {
                int square = __builtin_ctzll(to);
                Bitboard possibleFroms = rankMask(square) | fileMask(square) | diagonalMask(square) | antiDiagMask(square);

                from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];
            } else if (piece == Knight) {
                int square = __builtin_ctzll(to);
                Bitboard possibleFroms = knightMask(square);

                from = possibleFroms & board.bitboards[std::make_pair(turn, piece)];
            } else {
                // Assumes it is a pawn capture
                char file = move[0];
                Bitboard possibleFroms = turn == White ? soWeOne(to) | soEaOne(to) : noWeOne(to) | noEaOne(to);

                from = possibleFroms & fileMask((int)file - (int)'a');
            }

            return {turn, piece, from, to, Capture, NullPiece};
        } else if (move.find('=') != std::string::npos) {
            try {
                to = getSquare(move.substr(0, 2));
            } catch (std::string e) {
                throw std::invalid_argument("Square could not be parsed");
            }
            Piece promoPiece = pieceMap[move[3]];

            Bitboard from = turn == White ? to >> 8 : to << 8;

            return {turn, Pawn, from, to, Promotion, promoPiece};
        }
    }

    throw std::invalid_argument("Move could not be parsed");
}
