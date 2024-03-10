//---------------------------------------------------------------------------

#ifndef TimeManagerH
#define TimeManagerH
//---------------------------------------------------------------------------

#include <chrono>
#include <vcl.h>

#include "Logger.h"


class TimeManager {

    private:
    	std::chrono::time_point<std::chrono::system_clock> startTime;
    	std::chrono::time_point<std::chrono::system_clock> endTime;

    public:
        TimeManager();
        void startTimer();
    	void endTimer();
        long getElapsedTime() const;

        static UnicodeString getCurrentTime();
        static UnicodeString getCurrentDate();
        static UnicodeString getCurrentDateTime();

};
#endif
