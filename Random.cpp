//---------------------------------------------------------------------------

#pragma hdrstop

#include "Random.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


namespace Random {
	bool initialized = false;
    std::mt19937 gen;

    int getRandom(int min, int max) {
        if (!initialized) {
			gen = std::mt19937(static_cast<unsigned int>(time(nullptr)));
            initialized = true;
		}

        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    }
}
