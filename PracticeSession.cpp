//---------------------------------------------------------------------------

#pragma hdrstop

#include "PracticeSession.h"
#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

PracticeSession::PracticeSession() {

	LOGGER(LogLevel::Debug, "Practice session created");
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
	return keyStatistics.getTotalCount();
}

void PracticeSession::setTotalCount(int _totalCount) {
	keyStatistics.setTotalCount(_totalCount);
}

void PracticeSession::incTotalCount() {
	keyStatistics.incTotalCount();
}

const int& PracticeSession::getCorrectCount() const {
	return keyStatistics.getCorrectCount();
}

void PracticeSession::setCorrectCount(int _correctCount) {
  keyStatistics.setCorrectCount(_correctCount);
}

void PracticeSession::incCorrectCount() {
	keyStatistics.incCorrectCount();
}

const int& PracticeSession::getMistakesCount() const {
	return keyStatistics.getMistakesCount();
}

void PracticeSession::setMistakesCount(int _mistakesCount) {
	keyStatistics.setMistakesCount(_mistakesCount);
}

void PracticeSession::incMistakesCount() {
	keyStatistics.incMistakesCount();
}

const bool PracticeSession::doIgnoreSeqMistakes() const{
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


