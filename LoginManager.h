//---------------------------------------------------------------------------

#ifndef LoginManagerH
#define LoginManagerH
//---------------------------------------------------------------------------

#include "SessionModule.h"

class LoginManager {

	private:
		SessionModule *sessionModule;

	public:
        void setSessionModule(SessionModule *_sessionModule);
		bool isValidLogin(const UnicodeString& input);
};

#endif
