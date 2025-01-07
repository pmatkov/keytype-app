//---------------------------------------------------------------------------

#ifndef GameEngineH
#define GameEngineH
//---------------------------------------------------------------------------

#include <memory>
#include <vector>
#include <queue>
#include "FlyingWord.h"
#include "Limit.h"
#include "GameStatistics.h"
#include "ISingleItemDisplay.h"
#include "IGameDisplay.h"

using namespace FWLimit;

class GameThread;
class KeystrokeProcessorThread;
class GameScoreThread;

enum class GameStatus {
	Started,
	Completed,
	Count,
	Unknown
};

class GameEngine {

	private:
    	ISingleItemDisplay &singleItemDisplay;
        IGameDisplay &gameDisplay;

        std::vector<UnicodeString> wordList;

		std::queue<FlyingWord> words;
        std::vector<FlyingWord> wordsOnDisplay;
		FWLimit::Limit gameArea;

		GameStatus gameStatus;
        GameStatistics gameStatistics;
        UnicodeString lastMatch;

		GameThread *gameThread = nullptr;
        KeystrokeProcessorThread *keystrokeProcessorThread = nullptr;
        GameScoreThread *gameScoreThread = nullptr;

        std::unique_ptr<TMutex> mutexWords;
        std::unique_ptr<TMutex> mutexScore;

		static std::vector<UnicodeString> enumStrings;

        template <typename T>
		void thTerminate(T *&thread);

	public:
		GameEngine(ISingleItemDisplay &_singleItemDisplay, IGameDisplay &_gameDisplay);

        void loadWordList(const UnicodeString &fileName);
        bool isWordListLoaded();

		void initializeGame(FWLimit::Limit _gameArea);

		void createWords(int count);
        void removeWord();
        void clearWords();
        const std::queue<FlyingWord> &getWords() const;
        FlyingWord getFirstWord() const;

        void addWordOnDisplay(const FlyingWord &word);
        void replaceWordOnDisplay(int index, const FlyingWord &word);
		void removeWordOnDisplay(int index);
		void clearWordsOnDisplay();
        const std::vector<FlyingWord> &getWordsOnDisplay() const;

		const GameStatus &getGameStatus() const;
		void setGameStatus(GameStatus _gameStatus);

        const GameStatistics &getGameStatistics() const;
		void setGameStatistics(GameStatistics _gameStatistics);

        void setLastMatch(const UnicodeString &_lastMatch);
        const UnicodeString &getLastMatch() const;

		FWLimit::Limit calculateLimit(int index, int count);

        UnicodeString getRndWord();
		int getRndWordCount(int min, int max);
		UnicodeString getRndColor();
		Speed getRndSpeed();
        Direction getRndDirection();

		int getDelay(int min, int max);

		void threadTerminate();
        void gameCleanup();

		static std::vector<UnicodeString>& getEnumStrings();

};


#endif
