//---------------------------------------------------------------------------

#pragma hdrstop

#include "PracticeSession.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


const User& PracticeSession::getUser() const {
	return user;
}
void PracticeSession::setUser(const User& _user) {
   user = _user;
}

const TextSource& PracticeSession::getTextSource() const {
	return textSource;
}
void PracticeSession::setTextSource(const TextSource& _textSource) {
	textSource = _textSource;
}

void PracticeSession::increaseCharIndex() {
	 textSource.increaseCharIndex();
}

void PracticeSession::decreaseCharIndex() {
	 textSource.decreaseCharIndex();
}


const bool& PracticeSession::isMistake() const {
	return mistake;
}

void PracticeSession::setMistake(bool _mistake) {
    mistake = _mistake;
}

const int& PracticeSession::getTotalCount() const {
	return totalCount;
}

void PracticeSession::setTotalCount(int _totalCount) {
	totalCount =_totalCount;
}

void PracticeSession::incTotalCount() {
	totalCount++;
}

const int& PracticeSession::getValidCount() const {
	  return validCount;
}

void PracticeSession::setValidCount(int _validCount) {
   validCount = _validCount;
}

void PracticeSession::incValidCount() {
	validCount++;
}

const int& PracticeSession::getMistakesCount() const {
	return mistakesCount;
}

void PracticeSession::setMistakesCount(int _mistakesCount) {

	 mistakesCount = _mistakesCount;
}

void PracticeSession::incMistakesCount() {
	mistakesCount++;
}

const bool PracticeSession::isIgnoreSeqMistakes() const{
	return ignoreSeqMistakes;
}

void PracticeSession::setIgnoreSeqMistakes(bool _ignoreSeqMistakes) {
	 ignoreSeqMistakes = _ignoreSeqMistakes;
}

const bool PracticeSession::isStopOnMistake() const {
   return stopOnMistake;
}

void PracticeSession::setStopOnmistake(bool _stopOnMistake) {
   stopOnMistake = _stopOnMistake;
}

const bool PracticeSession::isActive() const {
	return active;
}

void PracticeSession::setActive(bool _active) {
	active = _active;
}

const bool PracticeSession::isPaused() const {
	return paused;
}

void PracticeSession::setPaused(bool _paused) {
	paused = _paused;
}


