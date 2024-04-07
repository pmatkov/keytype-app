//---------------------------------------------------------------------------

#ifndef FactoryH
#define FactoryH
//---------------------------------------------------------------------------
#include <memory>
#include "Dictionary.h"
#include "GameEngine.h"
#include "ISingleItemDisplay.h"
#include "IMultiItemDisplay.h"
#include "IGameDisplay.h"

 namespace ModelFactory {

   	template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    std::unique_ptr<Dictionary> createDictionary(ISingleItemDisplay &singleItemDisplay, IMultiItemDisplay &multiItemDisplay);

	std::unique_ptr<GameEngine> createGameEngine(ISingleItemDisplay &singleItemDisplay, IGameDisplay &gameDisplay);

 }

#endif
