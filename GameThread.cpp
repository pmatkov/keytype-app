//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameThread.h"
#include "FlyingWord.h"
#include "Random.h"
#include <chrono>
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall GameThread::GameThread(bool CreateSuspended, IGameDisplay &_gameDisplay, GameEngine &_gameEngine, TMutex &_mutexWords)
		: TThread(CreateSuspended), gameDisplay(_gameDisplay), gameEngine(_gameEngine), mutexWords(_mutexWords) {
		 FreeOnTerminate = false;
		}

void __fastcall GameThread::Execute()
{

	auto start = std::chrono::high_resolution_clock::now();
	int batchDelay = 0;
	int wordDelay = gameEngine.getDelay(1000, 3000);

	while  (!Terminated) {
		auto end = std::chrono::high_resolution_clock::now();

		// create new words if none available
		if (!gameEngine.getWords().size() && !gameEngine.getWordsOnDisplay().size() && \
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > batchDelay) {

			gameEngine.createWords(gameEngine.getRndWordCount(2, 5));
			batchDelay = 2000;
			start = std::chrono::high_resolution_clock::now();
		}
		// prepare words for display
		if (gameEngine.getWords().size() && \
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > wordDelay) {

            FlyingWord word = gameEngine.getFirstWord();

			Synchronize([this, word]() {
				UnicodeString text = word.getText();
				UnicodeString color = word.getColor();
				gameDisplay.createTextControl(text, color);
			 });


            int index = gameEngine.getWordsOnDisplay().size();
			int height = gameDisplay.getTextHeight(index);
			int width = gameDisplay.getTextWidth(index);

            word.setOuterLimit(word.getOuterLimit().getBottom() - height, word.getOuterLimit().getRight() - width);

            int maxInnerRange = Random::getRandom(0, (word.getOuterLimit().getBottom() - word.getOuterLimit().getTop())/ 2 - (height/ 2));
            word.setInnerLimit(word.getOuterLimit().getTop() + maxInnerRange, word.getOuterLimit().getBottom() - maxInnerRange);

			word.setMaxHDistance(Random::getRandom(0, (word.getOuterLimit().getRight() - word.getPosition().getX()) / 2));

            gameEngine.removeWord();
            gameEngine.addWordOnDisplay(word);

			start = std::chrono::high_resolution_clock::now();
			wordDelay = gameEngine.getDelay(1000, 3000);

		}

        // display or remove words
        mutexWords.Acquire();

		if (gameEngine.getWordsOnDisplay().size()) {

			for (int i = 0; i < gameEngine.getWordsOnDisplay().size(); i++) {

            	FlyingWord word = gameEngine.getWordsOnDisplay()[i];

				int x = word.getPosition().getX();
				int y = word.getPosition().getY();

				int limitRight = word.getOuterLimit().getRight();
				int moveRight = limitRight > x + (static_cast<int>(word.getSpeed())) ? static_cast<int>(word.getSpeed()) : limitRight - x;

				int limitTop = word.getInnerLimit().getTop();
				int moveUp = limitTop < y - (static_cast<int>(word.getSpeed())) ? static_cast<int>(word.getSpeed()) : y - limitTop;

				int limitBottom = word.getInnerLimit().getBottom();
				int moveDown = limitBottom > y + (static_cast<int>(word.getSpeed())) ? static_cast<int>(word.getSpeed()) : limitBottom - y;

				if (moveRight) {

					if (word.getDirection() == Direction::Neutral && word.getMaxHDistance()) {
                    	word.setPosition(Position(x + moveRight, y));
                       	word.setMaxHDistance(word.getMaxHDistance() - moveRight);
					}
					else if (word.getDirection() == Direction::Up) {
                    	word.setPosition(Position(x + moveRight, y - moveUp));
					}
					else if (word.getDirection() == Direction::Down) {
                    	word.setPosition(Position(x + moveRight, y + moveDown));
					}

					if (y - moveUp == limitTop || y + moveDown == limitBottom || !word.getMaxHDistance()) {
					   word.setDirection(gameEngine.getRndDirection());
					   word.setMaxHDistance(Random::getRandom(0, (word.getOuterLimit().getRight() - word.getPosition().getX()) / 2));
					}

					Synchronize([this, word, i]() {
						int x = word.getPosition().getX();
						int y = word.getPosition().getY();
						gameDisplay.moveTextControl(i, x, y);
					 });
                     gameEngine.replaceWordOnDisplay(i, word);

				}
                else {
					Synchronize([this, i]() {gameDisplay.removeTextControl(i);});
					gameEngine.removeWordOnDisplay(i);
				}

			}


		}
        mutexWords.Release();
		Sleep(10);
	}
}

