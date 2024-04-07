//---------------------------------------------------------------------------

#ifndef GameScoreThreadH
#define GameScoreThreadH
//---------------------------------------------------------------------------

#include "GameEngine.h"

class GameScoreThread : public TThread
{
    private:
        ISingleItemDisplay &singleItemDisplay;
        GameEngine &gameEngine;
        TMutex &mutexScore;
        TEvent &wordMatchEvent;
        TEvent &terminateEvent;

    protected:
        void __fastcall Execute();

    public:
        __fastcall GameScoreThread(bool CreateSuspended, ISingleItemDisplay &_singleItemDisplay, GameEngine &_gameEngine, TMutex &_mutexScore, TEvent &_wordMatchEvent, TEvent &_terminateEvent);
};

#endif
