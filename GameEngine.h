//---------------------------------------------------------------------------

#ifndef GameEngineH
#define GameEngineH
//---------------------------------------------------------------------------

#include <memory>
#include <vector>
#include "GameArea.h"
#include "FlyingWord.h"
#include "IDisplay.h"
#include "IGameDisplay.h"

enum class GameStatus {
	Started,
	Completed,
	Count,
	Unknown
};

class GameEngine {

    private:
        IDisplay &uiDisplay;
        IGameDisplay &gameDisplay;

        std::vector<FlyingWord> flyingWords;
        GameArea gameArea;
        GameStatus gameStatus;
        std::vector<UnicodeString> colors;

        int wordsDisplayed = 0;

        static std::vector<UnicodeString> enumStrings;

    public:
      	GameEngine(IDisplay &_uiDisplay, IGameDisplay &_gameDisplay);

        void initializeGame(int top, int bottom, int left, int right);
        Limit getLimit(int count, int index);

        void createWords(int count);

        int getNumberOfWords(int min, int max);
        UnicodeString getColor();
        Speed getSpeed();
        int getStartDelay(int min, int max);

        int getWordsDisplayed(

//        void setGameStatus(GameStatus status);

        static std::vector<UnicodeString>& getEnumStrings();

};


#endif
