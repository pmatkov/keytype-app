//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameScoreThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall GameScoreThread::GameScoreThread(bool CreateSuspended, ISingleItemDisplay &_singleItemDisplay, GameEngine &_gameEngine, TMutex &_mutexScore, TEvent &_wordMatchEvent, TEvent &_terminateEvent)
		: TThread(CreateSuspended), singleItemDisplay(_singleItemDisplay), gameEngine(_gameEngine), mutexScore(_mutexScore), wordMatchEvent(_wordMatchEvent), terminateEvent(_terminateEvent) {
		 	FreeOnTerminate = false;
		}


void GameScoreThread::Execute()
{

    THandleObject* handles[2] = {&wordMatchEvent, &terminateEvent};

    while (!Terminated) {
        THandleObject* signaledObj;
        TWaitResult result = THandleObject::WaitForMultiple(handles, INFINITE, false, signaledObj, false, 2);

        if (signaledObj == &wordMatchEvent) {

            /* get last matched word
          		(synchronize with keystrokeProcessorThread) */

            mutexScore.Acquire();
            UnicodeString word = gameEngine.getLastMatch();
            mutexScore.Release();

            Synchronize([this, word]() {singleItemDisplay.setItemSingleItemControl("LastWord", word);});

            GameStatistics gs = gameEngine.getGameStatistics();

            int currentMatchCount = gs.getMatchCount();
            gs.setMatchCount(currentMatchCount + 1);

            int currentPoints = gs.getPoints();
            int newPoints = GameStatistics::calculatePoints(word);
            gs.setPoints(currentPoints + newPoints);

            gameEngine.setGameStatistics(gs);

            Synchronize([this, currentMatchCount]() {singleItemDisplay.setItemSingleItemControl("MatchCount", currentMatchCount + 1);});
            Synchronize([this, currentPoints, newPoints]() {singleItemDisplay.setItemSingleItemControl("Points", currentPoints + newPoints);});
        }
        else {
            break;
        }
    }
}
