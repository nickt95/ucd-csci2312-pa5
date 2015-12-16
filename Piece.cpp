#include "Game.h"
#include "Piece.h"

unsigned int Gaming::Piece::__idGen = 0;

Gaming::Piece::Piece(const ::Gaming::Game &g, const ::Gaming::Position &p): __game(g), __position(p), __id(__idGen++) {

}

std::ostream &Gaming::operator<<(std::ostream &os, const Gaming::Piece &piece) {
    piece.myPrint(os);
    return os;
}
