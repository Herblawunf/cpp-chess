#include "bitboards.h"

const Bitboard notAFile = 0xfefefefefefefefe;
const Bitboard notHFile = 0x7f7f7f7f7f7f7f7f;

Bitboard soutOne (Bitboard b) {return  b >> 8;}
Bitboard nortOne (Bitboard b) {return  b << 8;}
Bitboard eastOne (Bitboard b) {return (b << 1) & notAFile;}
Bitboard noEaOne (Bitboard b) {return (b << 9) & notAFile;}
Bitboard soEaOne (Bitboard b) {return (b >> 7) & notAFile;}
Bitboard westOne (Bitboard b) {return (b >> 1) & notHFile;}
Bitboard soWeOne (Bitboard b) {return (b >> 9) & notHFile;}
Bitboard noWeOne (Bitboard b) {return (b << 7) & notHFile;}

Bitboard indexBoard(int index) {
    return 1ULL << index;
}

Bitboard exploreStraight(Bitboard from, Bitboard to) {
    if (from == to) {
        return 0;
    }

    Bitboard explore = from;

    // First explore north
    Bitboard nort = 0;
    while (true) {
        nort |= explore;
        if (explore == 0) {
            nort = 0;
            break;
        }
        if (explore == to) {
            break;
        }
        explore = nortOne(explore);
    }
    if (nort != 0) {
        return nort;
    }
    explore = from;

    // Now explore south
    Bitboard sout = 0;
    while (true) {
        sout |= explore;
        if (explore == 0) {
            sout = 0;
            break;
        }
        if (explore == to) {
            break;
        }
        explore = soutOne(explore);
    }
    if (sout != 0) {
        return sout;
    }
    explore = from;

    // Now explore east
    Bitboard east = 0;
    while (true) {
        east |= explore;
        if (explore == 0) {
            east = 0;
            break;
        }
        if (explore == to) {
            break;
        }
        explore = eastOne(explore);
    }
    if (east != 0) {
        return east;
    }
    explore = from;

    // Lastly explore west
    Bitboard west = 0;
    while (true) {
        west |= explore;
        if (explore == 0) {
            west = 0;
            break;
        }
        if (explore == to) {
            break;
        }
        explore = westOne(explore);
    }
    if (west != 0) {
        return west;
    }

    // Otherwise there is no straight path between the two points
    return 0;
}

Bitboard rankMask(int sq) {return  0xff << (sq & 56);}

Bitboard fileMask(int sq) {return 0x0101010101010101 << (sq & 7);}
