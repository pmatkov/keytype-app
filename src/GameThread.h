//---------------------------------------------------------------------------

#ifndef GameThreadH
#define GameThreadH
//---------------------------------------------------------------------------

#include <vcl.h>
#include "IGameDisplay.h"
#include "GameEngine.h"

class GameThread : public TThread
{
private:
    IGameDisplay &gameDisplay;
	GameEngine &gameEngine;
    TMutex &mutexWords;

protected:
	void __fastcall Execute();

public:
    __fastcall GameThread(bool CreateSuspended, IGameDisplay &_gameDisplay, GameEngine &_gameEngine, TMutex &_mutexWords);
};



#endif
