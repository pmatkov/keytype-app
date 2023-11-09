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

const TextSource& PracticeSession::getTextsource() const {
	return textsource;
}
void PracticeSession::setTextsource(const TextSource& _textsource) {
	textsource = _textsource;
}

void PracticeSession::increaseCurrentCharIndex() {
	 textsource.increaseCurrentCharIndex();
}

void PracticeSession::decreaseCurrentCharIndex() {
	 textsource.decreaseCurrentCharIndex();
}

const bool& PracticeSession::isMistake() const {
	return mistake;
}

void PracticeSession::setMistake(bool _mistake) {
    mistake = _mistake;
}

const int& PracticeSession::getMistakesCount() const {
	return mistakesCount;
}
void PracticeSession::setMistakesCount(int _mistakesCount) {

	 mistakesCount = _mistakesCount;
}

const bool PracticeSession::isPaused() const {
	return paused;
}

void PracticeSession::setPaused(bool _paused) {
	paused = _paused;
}


