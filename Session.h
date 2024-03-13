//---------------------------------------------------------------------------

#ifndef SessionH
#define SessionH
//---------------------------------------------------------------------------

#include "UUIDGenerator.h"
#include "TimeManager.h"

class Session
{
    private:
        boost::uuids::uuid sessionUuid;
        std::chrono::time_point<std::chrono::system_clock> sessionStart;
    	std::chrono::time_point<std::chrono::system_clock> sessionEnd;

	public:
        Session();

        void setSessionStart();
 		void setSessionEnd();
        long getElapsedTime() const;

};

#endif
