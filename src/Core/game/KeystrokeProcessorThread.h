//---------------------------------------------------------------------------

#ifndef KeystrokeProcessorThreadH
#define KeystrokeProcessorThreadH
//---------------------------------------------------------------------------

#include <queue>
#include "GameEngine.h"

class KeystrokeProcessorThread : public TThread
{
    private:
        IGameDisplay &gameDisplay;
        GameEngine &gameEngine;

        std::queue<wchar_t> &keystrokeQueue;

        TCriticalSection &criticalSection;
        TMutex &mutexWords;
        TMutex &mutexScore;

        TEvent &keyStrokeEvent;
        TEvent &wordMatchEvent;
        TEvent &terminateEvent;

    protected:
        void __fastcall Execute();

    public:
        __fastcall KeystrokeProcessorThread(bool CreateSuspended, IGameDisplay &_gameDisplay, GameEngine &_gameEngine, std::queue<wchar_t> &_keystrokeQueue, TCriticalSection &_criticalSection, \
        TMutex &_mutexWords, TMutex &_mutexScore, TEvent &_keyStrokeEvent, TEvent &_wordMatchEvent, TEvent &_terminateEvent);
};

#endif
