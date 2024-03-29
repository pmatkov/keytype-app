//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

GameThread::GameThread(bool CreateSuspended, IGameDisplay &_gameDisplay, GameEngine &_gameEngine)
        : TThread(CreateSuspended), gameDisplay(_gameDisplay), gameEngine(_gameEngine) {}

void __fastcall GameThread::UpdateLabel()
{
    label->Left = gameLogic.getX();
    label->Top = gameLogic.getY();
}

void __fastcall GameThread::Execute()
{

    const auto start = high_resolution_clock::now();
    int startDelay = gameEngine.getStartDelay(500, 3000);

    while (!Terminated)
    {

        const auto end = std::chrono::high_resolution_clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > startDelay && m) {
           startDelay
        }



        Synchronize(&UpdateLabel);
        Sleep(10);
    }
}