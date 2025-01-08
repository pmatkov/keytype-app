//---------------------------------------------------------------------------

#pragma hdrstop

#include "Position.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Position::Position(int _x, int _y) : x(_x), y(_y) {}

int Position::getX() const {
    return x;
}

void Position::setX(int _x) {
    x = _x;
}

int Position::getY() const {
    return y;
}

void Position::setY(int _y) {
    y = _y;
}