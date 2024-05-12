//---------------------------------------------------------------------------

#pragma hdrstop

#include "TypingSession.h"
#include "TextUtils.h"
#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TypingSession::TypingSession() {

	LOGGER(LogLevel::Debug, "Typing session created");
}

const TextSource& TypingSession::getTextSource() const {
	return textSource;
}
void TypingSession::setTextSource(const TextSource& _textSource) {
	textSource = _textSource;
}

int TypingSession::getCharCount() const {
    return charCount;
}

void TypingSession::setCharCount(int _charCount) {
    charCount = _charCount;
}

int TypingSession::getWordCount() const {
    return wordCount;
}

void TypingSession::setWordCount(int _wordCount) {
    wordCount = _wordCount;
}

void TypingSession::increaseCorrectKey(wchar_t key) {

  if (keyStatistics.find(key) == keyStatistics.end()) {
        keyStatistics[key] = KeyStatistics(key);
  }
  keyStatistics[key].increaseCorrect();
}

void TypingSession::increaseMistakeKey(wchar_t key) {

  if (keyStatistics.find(key) == keyStatistics.end()) {
        keyStatistics[key] = KeyStatistics(key);
  }
  keyStatistics[key].increaseMistake();
}

std::map<wchar_t, KeyStatistics> &TypingSession::getKeyStatistics() {
     return keyStatistics;
}

void TypingSession::increaseCharIndex() {
	 textSource.increaseCharIndex();
}

void TypingSession::decreaseCharIndex() {
	 textSource.decreaseCharIndex();
}

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

double TypingSession::getSpeed() {

 	return calculateSpeed();
}

double TypingSession::getAvgSpeed() {
    double sum = 0;

    for (int sp: speedReadings) {
      sum += sp;
    }

    int readingCount = speedReadings.size();
 	return sum/ readingCount;
}

double TypingSession::calculateSpeed() {

	if (!typedWords || !getElapsedTime()) {
        return 0;
    }

    double speed = typedWords/ (getElapsedTime()/ 60.0);

    speedReadings.push_back(speed);
    return speed;
}

double TypingSession::getAccuracy() {

    return calculateAccuracy();
}

double TypingSession::calculateAccuracy() {

    if (!textSource.getCharCount()) {
        return 100;
    }

    double accuracy = ((double)(textSource.getCharCount() - mistakes) / textSource.getCharCount()) * 100.0;
    return accuracy;
}


const SessionStatus& TypingSession::getSessionStatus() const {
	return sessionStatus;
}

void TypingSession::setSessionStatus(const SessionStatus &_sessionStatus) {
	sessionStatus = _sessionStatus;
}

const LessonGoal& TypingSession::getLessonGoal() const {
    return lessonGoal;
}

void TypingSession::setLessonGoal(const LessonGoal &_lessonGoal) {
  	lessonGoal = _lessonGoal;
}

int TypingSession::getGoalValue() const {
    return goalValue;
}

void TypingSession::setGoalValue(int _goalValue) {
    goalValue = _goalValue;
}

int TypingSession::getDifficulty() const {
   return difficulty;
}

void TypingSession::setDifficulty(int _difficulty) {
   difficulty = _difficulty;
}

const std::vector<UnicodeString>& TypingSession::getLessonGoalStrings() {
    return lessonGoalStrings;
}

void TypingSession::resetSessionData() {

    typedWords = 0;
    mistakes = 0;
    speedReadings.clear();
    keyStatistics.clear();

}

std::vector<UnicodeString> TypingSession::lessonGoalStrings = {"speed", "accuracy"};

