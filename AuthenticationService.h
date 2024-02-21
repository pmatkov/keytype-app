//---------------------------------------------------------------------------

#ifndef AuthenticationServiceH
#define AuthenticationServiceH
//---------------------------------------------------------------------------

#include "MainSession.h"

class  AuthenticationService {

	private:
        MainSession *mainSession;

	public:
        AuthenticationService(MainSession *_mainSession);

    	bool loginUser(const UnicodeString& username);
        bool logoutUser();
};

#endif
