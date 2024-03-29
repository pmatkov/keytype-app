//---------------------------------------------------------------------------

#pragma hdrstop

#include "TypingSession.h"
#include "TextUtils.h"
#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TypingSession::TypingSession() {

//    totalWords = TextUtils::countWords(textSource.getText());
//    totalChars = textSource.getText().Length();

	LOGGER(LogLevel::Debug, "Practice session created");
}

const TextSource& TypingSession::getTextSource() const {
	return textSource;
}
void TypingSession::setTextSource(const TextSource& _textSource) {
	textSource = _textSource;
}

void TypingSession::increaseCharIndex() {
	 textSource.increaseCharIndex();
}

void TypingSession::decreaseCharIndex() {
	 textSource.decreaseCharIndex();
}

//int TypingSession::getWordCount() const {
//	return textSource.getWordCount();
//}
//
//int TypingSession::getTotalChars() const {
//	return texttotalChars;
//}


void TypingSession::increaseTypedWords() {
  typedWords++;
}

int TypingSession::getMistakes() const {
	return mistakes;
}

void TypingSession::setMistakes(int _mistakes) {
	mistakes = _mistakes;
}

void TypingSession::increaseMistakes() {
	mistakes++;
}

double TypingSession::getSpeed() const {
	return calculateSpeed();
}

double TypingSession::calculateSpeed() const {

	if (!typedWords) {
        return 0;
    }
    return typedWords/ (getElapsedTime()/ 60.0);
}

double TypingSession::getAccuracy() const {
    return calculateAccuracy();
}

double TypingSession::calculateAccuracy() const {

    if (!textSource.getCharCount()) {
        return 100;
    }
    return ((double)(textSource.getCharCount() - mistakes) / textSource.getCharCount()) * 100.0;
}

const SessionStatus& TypingSession::getSessionStatus() const {
	return sessionStatus;
}

void TypingSession::setSessionStatus(const SessionStatus &_sessionStatus) {
	sessionStatus = _sessionStatus;
}

