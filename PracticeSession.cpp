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


