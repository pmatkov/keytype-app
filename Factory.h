//---------------------------------------------------------------------------

#ifndef FactoryH
#define FactoryH
//---------------------------------------------------------------------------
#include <memory>
#include "Dictionary.h"
#include "GameEngine.h"
#include "IDisplay.h"
#include "IGameDisplay.h"

 namespace ModelFactory {

   	template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    std::unique_ptr<Dictionary> createDictionary(IDisplay &uiDisplay);

    std::unique_ptr<GameEngine> createGameEngine(IDisplay &uiDisplay, IGameDisplay &gameDisplay);

 }

#endif
