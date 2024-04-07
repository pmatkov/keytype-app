//---------------------------------------------------------------------------

#pragma hdrstop

#include "KeystrokeProcessorThread.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

KeystrokeProcessorThread::KeystrokeProcessorThread(bool CreateSuspended, IGameDisplay &_gameDisplay, GameEngine &_gameEngine, std::queue<wchar_t> &_keystrokeQueue, TCriticalSection &_criticalSection, \
 TMutex &_mutexWords, TMutex &_mutexScore, TEvent &_keyStrokeEvent, TEvent &_wordMatchEvent, TEvent &_terminateEvent)
        :  TThread(CreateSuspended), gameDisplay(_gameDisplay), gameEngine(_gameEngine), keystrokeQueue(_keystrokeQueue), criticalSection(_criticalSection),  mutexWords(_mutexWords), mutexScore(_mutexScore), \
        keyStrokeEvent(_keyStrokeEvent), wordMatchEvent(_wordMatchEvent), terminateEvent(_terminateEvent) {
        	FreeOnTerminate = false;
        }

void KeystrokeProcessorThread::Execute()
{
	UnicodeString word = "";
    bool wordMatch;

    THandleObject* handles[2] = {&keyStrokeEvent, &terminateEvent};

    while (!Terminated) {
        THandleObject* signaledObj;
    	TWaitResult result = THandleObject::WaitForMultiple(handles, INFINITE, false, signaledObj, false, 2);

        if (signaledObj == &keyStrokeEvent) {

        	wordMatch  = false;

            criticalSection.Acquire();
            while (!keystrokeQueue.empty())
            {
                word += UnicodeString(keystrokeQueue.front());
                keystrokeQueue.pop();
            }
            criticalSection.Release();

            mutexWords.Acquire();
            for (int i = 0; i < gameEngine.getWordsOnDisplay().size(); i++) {

                if (gameEngine.getWordsOnDisplay()[i].getText() == word) {

                    wordMatch  = true;
                    Synchronize([this, i]() {gameDisplay.removeTextControl(i);});
                    gameEngine.removeWordOnDisplay(i);
                    break;
                }
            }
            mutexWords.Release();

            mutexScore.Acquire();
            if (wordMatch) {
                gameEngine.setLastMatch(word);
                wordMatchEvent.SetEvent();
            }
            mutexScore.Release();

            word = "";
        }
        else {
            break;
        }
    }
}
