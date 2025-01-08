//---------------------------------------------------------------------------

#ifndef SessionH
#define SessionH
//---------------------------------------------------------------------------

#include "TimeManager.h"

class Session
{
    private:
        std::chrono::time_point<std::chrono::system_clock> startTime;
    	std::chrono::time_point<std::chrono::system_clock> endTime;

	public:
        Session();

        void startTimer();
 		void stopTimer();
        long getElapsedTime() const;

};

#endif
