//---------------------------------------------------------------------------
#pragma hdrstop

#include "GameEngine.h"
#include "EnumUtils.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "Random.h"
#include "FlyingWordsFrame.h"
#include "GameThread.h"
#include "KeystrokeProcessorThread.h"
#include "GameScoreThread.h"

#include "EFileNotFoundException.h"

#pragma package(smart_init)

GameEngine::GameEngine(ISingleItemDisplay &_singleItemDisplay, IGameDisplay &_gameDisplay) : singleItemDisplay(_singleItemDisplay), gameDisplay(_gameDisplay)  {

	mutexWords = std::make_unique<TMutex>(false);
    mutexScore = std::make_unique<TMutex>(false);
}

void GameEngine::loadWordList(const UnicodeString &fileName) {

	std::optional<UnicodeString> buffer;

    try {
        UnicodeString path = FileUtils::createAbsolutePath("WordList\\" + fileName, true);
        buffer = FileUtils::readFromTextFile(path);
    } catch (CustomExceptions::EFileNotFoundException &ex) {
        LOGGER(LogLevel::Fatal, ex.getMessage());
    }

    if (buffer.has_value()) {
        wordList = TextUtils::splitToTokens(*buffer);
    }
}

bool GameEngine::isWordListLoaded() {
    return  wordList.size();
}

void GameEngine::initializeGame(FWLimit::Limit _gameArea) {

	if (!gameThread && !keystrokeProcessorThread && !gameScoreThread) {

    	gameArea = _gameArea;

        TFrFlyingWords &flyingWords = static_cast<TFrFlyingWords&>(gameDisplay);

        // create threads

        gameThread = new GameThread(false, gameDisplay, *this, *mutexWords);
        keystrokeProcessorThread = new KeystrokeProcessorThread(false, gameDisplay, *this, flyingWords.getKeyStrokeQueue(),\
         flyingWords.getCriticalSection(), *mutexWords, *mutexScore, flyingWords.getKeyStrokeEvent(), flyingWords.getWordMatchEvent(), flyingWords.getTerminateEvent());
        gameScoreThread = new GameScoreThread(false, singleItemDisplay, *this, *mutexScore, flyingWords.getWordMatchEvent(), flyingWords.getTerminateEvent());

        gameStatus = GameStatus::Started;
	}

 }

void GameEngine::createWords(int count) {

   for (int i = 0; i < count; i++) {

        FWLimit::Limit limit = calculateLimit(i, count);
        words.push(FlyingWord(getRndWord(), limit, Position(0, (limit.getBottom() - limit.getTop())/ 2), getRndSpeed(), getRndDirection(), getRndColor(), 0));
   }
}

void GameEngine::removeWord() {
   	words.pop();
}

void GameEngine::clearWords() {
   	while (!words.empty()) {
        words.pop();
    }
}

const std::queue<FlyingWord> &GameEngine::getWords() const {
	return words;
}

FlyingWord GameEngine::getFirstWord() const {
	return words.front();
}

void GameEngine::addWordOnDisplay(const FlyingWord &word) {
     wordsOnDisplay.push_back(word);
}

void GameEngine::replaceWordOnDisplay(int index, const FlyingWord &word) {
    wordsOnDisplay[index] = word;
}

void GameEngine::removeWordOnDisplay(int index) {
   wordsOnDisplay.erase(wordsOnDisplay.begin() + index);
}

void GameEngine::clearWordsOnDisplay() {
   wordsOnDisplay.clear();
}

const std::vector<FlyingWord> &GameEngine::getWordsOnDisplay() const {
     return wordsOnDisplay;
}

const GameStatus &GameEngine::getGameStatus() const {
	return gameStatus;
}

void GameEngine::setGameStatus(GameStatus _gameStatus) {
	gameStatus = _gameStatus;
}

const GameStatistics &GameEngine::getGameStatistics() const {
   return gameStatistics;
}

void GameEngine::setGameStatistics(GameStatistics _gameStatistics) {
    gameStatistics = _gameStatistics;
}

void GameEngine::setLastMatch(const UnicodeString &_lastMatch) {
     lastMatch = _lastMatch;
}
const UnicodeString &GameEngine::getLastMatch() const {
    return lastMatch;
}

FWLimit::Limit GameEngine::calculateLimit(int index, int count) {
	 int areaHeight = gameArea.getBottom() - gameArea.getTop();
	 int rowHeight = areaHeight/ count;
	 return FWLimit::Limit(gameArea.getTop() + index * rowHeight, gameArea.getTop() + index * rowHeight + rowHeight, gameArea.getLeft(), gameArea.getRight());
}

UnicodeString GameEngine::getRndWord() {

	return wordList[Random::getRandom(0, wordList.size()-1)];
}

int GameEngine::getRndWordCount(int min, int max) {

	return Random::getRandom(min, max);
}

UnicodeString GameEngine::getRndColor() {

	const std::vector<UnicodeString> colors = {"clTeal", "clPurple", "clNavy", "clMaroon", "clFuchsia", "clOlive"};
    return colors[Random::getRandom(0, colors.size()-1)];
}

Speed GameEngine::getRndSpeed() {

	const std::vector<UnicodeString> speed = FlyingWord::getEnumSpeed();
	return EnumUtils::stringToEnum<Speed>(speed, speed[Random::getRandom(1, speed.size()-1)]);
}

Direction GameEngine::getRndDirection() {

	const std::vector<UnicodeString> direction = FlyingWord::getEnumDirection();
    return EnumUtils::stringToEnum<Direction>(direction, direction[Random::getRandom(0, direction.size()-1)]);
}

int GameEngine::getDelay(int min, int max) {
    return Random::getRandom(min, max);
}

template <typename T>
void GameEngine::thTerminate(T*& thread) {

   	if (thread != nullptr) {
		thread->Terminate();
		thread->WaitFor();
		FreeAndNil(thread);
	}
}

template void GameEngine::thTerminate<GameScoreThread>(GameScoreThread*&);
template void GameEngine::thTerminate<KeystrokeProcessorThread>(KeystrokeProcessorThread*&);
template void GameEngine::thTerminate<GameThread>(GameThread*&);

void GameEngine::threadTerminate() {

   	thTerminate(gameScoreThread);
    thTerminate(keystrokeProcessorThread);
    thTerminate(gameThread);
}


void GameEngine::gameCleanup()  {

    if (gameStatus == GameStatus::Started) {

    	gameDisplay.removeAllTextControls();
        clearWords();
        clearWordsOnDisplay();

        singleItemDisplay.setItemSingleItemControl("LastWord", "");
        singleItemDisplay.setItemSingleItemControl("MatchCount", "");
        singleItemDisplay.setItemSingleItemControl("TimeRemaining", "");
        singleItemDisplay.setItemSingleItemControl("Points", "");

        gameStatistics.resetStatistics();
        setGameStatus(GameStatus::Completed);
    }
}

std::vector<UnicodeString>& GameEngine::getEnumStrings() {
    return enumStrings;
}

std::vector<UnicodeString> GameEngine::enumStrings = {"started", "stopped"};
