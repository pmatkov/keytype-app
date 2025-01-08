//---------------------------------------------------------------------------

#pragma hdrstop

#include "KeyStatistics.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

KeyStatistics::KeyStatistics() {}
KeyStatistics::KeyStatistics(wchar_t _key): key (_key) {}
KeyStatistics::KeyStatistics(wchar_t _key, int _correct, int _mistake): key (_key), correct(_correct), mistake(_mistake) {}

wchar_t KeyStatistics::getKey() const {
 	return key;
}

int KeyStatistics::getCorrect() const {
	return correct;
}

void KeyStatistics::setCorrect(int _correct) {
   correct = _correct;
}

void KeyStatistics::increaseCorrect() {
	correct++;
}

int KeyStatistics::getMistake() const {
	return mistake;
}

void KeyStatistics::setMistake(int _mistake) {
	 mistake = _mistake;
}

void KeyStatistics::increaseMistake() {
	mistake++;
}

