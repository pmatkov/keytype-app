//---------------------------------------------------------------------------

#ifndef SessionH
#define SessionH
//---------------------------------------------------------------------------

#include "UUIDGenerator.h"
#include "TimeManager.h"

class Session
{

    protected:;
        boost::uuids::uuid sessionUuid;
        TimeManager timeManager;

	public:
        Session();
        virtual ~Session() = 0;

};

#endif
