//---------------------------------------------------------------------------

#pragma hdrstop

#include "Random.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


namespace Random {

    int getRandom(int min, int max) {

        static std::random_device rd;
    	static std::mt19937 gen(rd());

		std::uniform_int_distribution<> dist(min, max);

        return dist(gen);
    }

}