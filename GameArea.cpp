//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameArea.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

GameArea::GameArea() {}
GameArea::GameArea(int _top, int _bottom, int _left, int _right) : top(_top), bottom(_bottom), left(_left), right(_right) {}

int GameArea::getTop() const {
    return top;
}
int GameArea::getBottom() const {
    return bottom;
}
int GameArea::getLeft() const {
    return left;
}
int GameArea::getRight() const {
    return right;

}

