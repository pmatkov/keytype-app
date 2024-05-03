//---------------------------------------------------------------------------

#pragma hdrstop

#include "FlyingWord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FlyingWord::FlyingWord(const UnicodeString &_text, FWLimit::Limit _outerLimit, Position _position, Speed _speed, \
Direction _direction, const UnicodeString &_color, int _maxHDistance) : text(_text), outerLimit(_outerLimit), \
 position(_position), speed(_speed), direction(_direction), color(_color), maxHDistance(_maxHDistance) {}

const UnicodeString &FlyingWord::getText() const {
	return text;
}

const FWLimit::Limit &FlyingWord::getOuterLimit() const {
   return outerLimit;
}

const FWLimit::Limit &FlyingWord::getInnerLimit() const {
   return innerLimit;
}

const Position &FlyingWord::getPosition() const {
	return position;
}

void FlyingWord::setPosition(Position _position) {
	position = _position;
}

const Speed &FlyingWord::getSpeed() const {
   return speed;
}

const Direction &FlyingWord::getDirection() const {
	return direction;
}

void FlyingWord::setDirection(Direction _direction) {
   direction = _direction;
}

const UnicodeString &FlyingWord::getColor() const {
   return color;
}

const int FlyingWord::getMaxHDistance() const {
   return maxHDistance;
}

void FlyingWord::setMaxHDistance(int _maxHDistance) {
   maxHDistance = _maxHDistance;
}

void FlyingWord::setOuterLimit(int bottom, int right) {
   outerLimit.setBottom(bottom);
   outerLimit.setRight(right);
}

void FlyingWord::setInnerLimit(int top, int bottom) {
   innerLimit.setTop(top);
   innerLimit.setBottom(bottom);
}

std::vector<UnicodeString>& FlyingWord::getEnumSpeed() {
	return enumSpeed;
}

std::vector<UnicodeString>& FlyingWord::getEnumDirection() {
	return enumDirection;
}

std::vector<UnicodeString> FlyingWord::enumSpeed = {"slow", "normal", "fast"};

std::vector<UnicodeString> FlyingWord::enumDirection = {"up", "down", "neutral"};
