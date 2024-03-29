//---------------------------------------------------------------------------

#pragma hdrstop

#include "FlyingWord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FlyingWord::FlyingWord(const UnicodeString &_text, Limit _limit, Position _position, Speed _speed, const UnicodeString &_color) : \
text(_text), limit(_limit), position(_position), speed(_speed), color(_color) {}

std::vector<UnicodeString>& FlyingWord::getEnumStrings() {
    return enumStrings;
}

std::vector<UnicodeString> FlyingWord::enumStrings = {"fast", "normal", "slow"};
