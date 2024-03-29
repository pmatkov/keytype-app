//---------------------------------------------------------------------------

#ifndef GameThreadH
#define GameThreadH
//---------------------------------------------------------------------------

#include "IGameDisplay.h"
#include "GameEngine.h"

class GameThread : public TThread
{
private:
    IGameDisplay &gameDisplay;
    GameEngine &gameEngine;

protected:
    void __fastcall Execute();
    void __fastcall UpdateLabel();

public:
    __fastcall GameThread(bool CreateSuspended, IGameDisplay &_gameDisplay, GameEngine &_gameEngine);
    void __fastcall Execute();

};



#endif
