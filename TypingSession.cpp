//---------------------------------------------------------------------------

#pragma hdrstop

#include "TypingSession.h"
#include "TextUtils.h"
#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TypingSession::TypingSession() {

	LOGGER(LogLevel::Debug, "Created typing session");
}

const TextSource& TypingSession::getTextSource() const {
	return textSource;
}
void TypingSession::setTextSource(const TextSource& _textSource) {
	textSource = _textSource;
}

int TypingSession::getWordCount() const {
    return wordCount;
}

void TypingSession::setWordCount(int _wordCount) {
    wordCount = _wordCount;
}

int TypingSession::getCharCount() const {
    return charCount;
}

void TypingSession::setCharCount(int _charCount) {
    charCount = _charCount;
}

double TypingSession::getSpeed() {

	return speed;
}


double TypingSession::getAvgSpeed() {

    double sum = 0;
    int readingsCount = speedReadings.size();

    if (!readingsCount) {
       return sum;
    }

    for (int sp: speedReadings) {
      sum += sp;
    }

 	return sum/ readingsCount;
}

// current speed = chars/ session time

void TypingSession::calculateSpeed() {

	long elapsedTime = getElapsedTime();

	if ((textSource.getCharIndex()-1) && elapsedTime) {

        speed = ((textSource.getCharIndex()-1)/ 5) /(elapsedTime/ 60.0);

        // save current speed to buffer
        speedReadings.push_back(speed);
    }
}

double TypingSession::getAccuracy() {

	return accuracy;
}

// current accuracy = (correct chars/ total chars) * 100

void TypingSession::calculateAccuracy() {

    if (textSource.getCharCount()) {
        accuracy = ((double)(textSource.getCharCount() - mistakes) / textSource.getCharCount()) * 100.0;
    }
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


const SessionStatus& TypingSession::getSessionStatus() const {
	return sessionStatus;
}

void TypingSession::setSessionStatus(const SessionStatus &_sessionStatus) {
	sessionStatus = _sessionStatus;
}

const SessionType& TypingSession::getSessionType() const {
    return sessionType;
}

void TypingSession::setSessionType(const SessionType &_sessionType) {
    sessionType = _sessionType;
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

const std::vector<UnicodeString>& TypingSession::getSessionStatusStrings() {
    return sessionStatusStrings;
}

const std::vector<UnicodeString>& TypingSession::getSessionTypeStrings() {
    return sessionTypeStrings;
}

const std::vector<UnicodeString>& TypingSession::getLessonGoalStrings() {
    return lessonGoalStrings;
}

void TypingSession::setVirtualKeyboardVisible(bool _virtualKeyboardVisible) {
    virtualKeyboardVisible = _virtualKeyboardVisible;
}


bool TypingSession::isVirtualKeyboardVisible() {
     return virtualKeyboardVisible;
}


void TypingSession::initializeSession() {

    startTimer();
}

void TypingSession::resetSession() {

    speed = 0;
    accuracy = 100;
    typedWords = 0;
    mistakes = 0;
    speedReadings.clear();
    keyStatistics.clear();
    stopTimer();
}

std::vector<UnicodeString> TypingSession::sessionStatusStrings = {"initialized", "started", "completed",  "reset"};
std::vector<UnicodeString> TypingSession::sessionTypeStrings = {"practice", "lesson"};
std::vector<UnicodeString> TypingSession::lessonGoalStrings = {"speed", "accuracy"};

