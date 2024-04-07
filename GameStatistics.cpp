//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameStatistics.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void GameStatistics::resetStatistics() {
   matchCount = 0;
   points = 0;
}

int GameStatistics::getMatchCount() const {
    return matchCount;
}

void GameStatistics::setMatchCount(int _matchCount) {
	matchCount = _matchCount;
}

int GameStatistics::getPoints() const {
   	return points;
}

void GameStatistics::setPoints(int _points) {
   	points = _points;
}

int GameStatistics::calculatePoints(const UnicodeString &word) {
   	return word.Length() * 10;
}

