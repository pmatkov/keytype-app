//---------------------------------------------------------------------------

#ifndef SessionH
#define SessionH
//---------------------------------------------------------------------------

#include "TimeManager.h"

class Session
{
    private:
        std::chrono::time_point<std::chrono::system_clock> sessionStartTime;
    	std::chrono::time_point<std::chrono::system_clock> sessionEndTime;

	public:
        Session();

        void startSessionTimer();
 		void stopSessionTimer();
        long getElapsedTime() const;

};

#endif
