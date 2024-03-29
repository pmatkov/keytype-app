//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameEngine.h"
#include "EnumUtils.h"
#include "Random.h"
#include "GameThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

GameEngine::GameEngine(IDisplay &_uiDisplay, IGameDisplay &_gameDisplay) : uiDisplay(_uiDisplay), gameDisplay(_gameDisplay)  {
   colors = {"clWebDarkCyan", "clWebHotPink", "clWebSlateBlue", "clWebDarkGoldenRod", "clWebOrangeRed"};
}

void GameEngine::initializeGame(int top, int bottom, int left, int right) {

    gameArea = GameArea(top, bottom, left, right);
    gameStatus = GameStatus::Started;
    createWords(getNumberOfWords(1, 5));
    std::unique_ptr<GameThread> thread = std::make_unique<GameThread>(true, gameDisplay, *this);
    thread->Start();

}

//void GameEngine::setGameStatus(GameStatus status) {
//
//    gameStatus = status;
//}

void GameEngine::createWords(int wordCount) {

   for (int i = 0; i < wordCount; i++) {

   	Limit limit = getLimit(wordCount, i);
   	flyingWords.push_back(FlyingWord("proba", limit, Position(0, (limit.getBottom() - limit.getTop())/ 2), getSpeed(), getColor()));
   }

}

Limit GameEngine::getLimit(int wordCount, int index) {
     int areaHeight = gameArea.getBottom() - gameArea.getTop();
     int rowHeight = areaHeight/ wordCount;
     return Limit(index * rowHeight, index * rowHeight + rowHeight, gameArea.getLeft(), gameArea.getRight());
}

int GameEngine::getNumberOfWords(int min, int max) {
    return Random::getRandom(min, max);
}

UnicodeString GameEngine::getColor() {
    return colors[Random::getRandom(0, colors.size()-1)];
}

Speed GameEngine::getSpeed() {

    std::vector<UnicodeString> speed = FlyingWord::getEnumStrings();
    return EnumUtils::stringToEnum<Speed>(speed, speed[Random::getRandom(0, speed.size()-1)]);
}

int GameEngine::getStartDelay(int min, int max) {
    return Random::getRandom(min, max);
}


std::vector<UnicodeString>& GameEngine::getEnumStrings() {
    return enumStrings;
}

std::vector<UnicodeString> GameEngine::enumStrings = {"started", "stopped"};
