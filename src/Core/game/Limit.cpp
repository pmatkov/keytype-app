//---------------------------------------------------------------------------

#pragma hdrstop

#include "Limit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace FWLimit {

    Limit::Limit() {}

    Limit::Limit(int _top, int _bottom, int _left, int _right): top(_top), bottom(_bottom), left(_left), right(_right) {}

    int Limit::getTop() const {
        return top;
    }
    void Limit::setTop(int _top){
        top = _top;
    }

    int Limit::getBottom() const {
        return bottom;
    }
    void Limit::setBottom(int _bottom) {
        bottom = _bottom;
    }

    int Limit::getLeft() const {
        return left;
    }

    void Limit::setLeft(int _left) {
        left = _left;
    }

    int Limit::getRight() const {
        return right;
    }

    void Limit::setRight(int _right) {
        right = _right;
    }
}
