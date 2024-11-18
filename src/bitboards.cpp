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
