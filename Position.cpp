//---------------------------------------------------------------------------

#pragma hdrstop

#include "Position.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


Limit::Limit(int _top, int _bottom, int _left, int _right): top(_top), bottom(_bottom), left(_left), right(_right) {}

int Limit::getTop() const {
    return top;
}

int Limit::getBottom() const {
    return bottom;
}

int Limit::getLeft() const {
    return left;
}

int Limit::getRight() const {
    return right;
}

void Limit::setTop(int _top){
    top = _top;
}

void Limit::setBottom(int _bottom) {
    bottom = _bottom;
}

void Limit::setLeft(int _left) {
    left = _left;
}

void Limit::setRight(int _right) {
    right = _right;
}



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