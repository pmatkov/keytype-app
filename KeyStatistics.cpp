//---------------------------------------------------------------------------

#pragma hdrstop

#include "KeyStatistics.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const int& KeyStatistics::getTotalCount() const {
	return totalCount;
}

void KeyStatistics::setTotalCount(int _totalCount) {
	totalCount = _totalCount;
}

void KeyStatistics::incTotalCount() {
	totalCount++;
}

const int& KeyStatistics::getCorrectCount() const {
	return correctCount;
}

void KeyStatistics::setCorrectCount(int _correctCount) {
   correctCount = _correctCount;
}

void KeyStatistics::incCorrectCount() {
	correctCount++;
}

const int& KeyStatistics::getMistakesCount() const {
	return mistakesCount;
}

void KeyStatistics::setMistakesCount(int _mistakesCount) {

	 mistakesCount = _mistakesCount;
}

void KeyStatistics::incMistakesCount() {
	mistakesCount++;
}

