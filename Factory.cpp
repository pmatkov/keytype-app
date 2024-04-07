//---------------------------------------------------------------------------

#pragma hdrstop

#include "Factory.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

 namespace ModelFactory {

    std::unique_ptr<Dictionary> createDictionary(ISingleItemDisplay &singleItemDisplay, IMultiItemDisplay &multiItemDisplay) {
        return std::make_unique<Dictionary>(singleItemDisplay, multiItemDisplay);
    }

	std::unique_ptr<GameEngine> createGameEngine(ISingleItemDisplay &singleItemDisplay, IGameDisplay &gameDisplay) {
        return std::make_unique<GameEngine>(singleItemDisplay, gameDisplay);
    }

 }
