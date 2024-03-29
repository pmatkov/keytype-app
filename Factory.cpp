//---------------------------------------------------------------------------

#pragma hdrstop

#include "Factory.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

 namespace ModelFactory {

    std::unique_ptr<Dictionary> createDictionary(IDisplay &uiDisplay) {
        return std::make_unique<Dictionary>(uiDisplay);
    }

    std::unique_ptr<GameEngine> createGameEngine(IDisplay &uiDisplay, IGameDisplay &gameDisplay) {
        return std::make_unique<GameEngine>(uiDisplay, gameDisplay);
    }

 }
