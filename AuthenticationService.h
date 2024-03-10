//---------------------------------------------------------------------------

#ifndef AuthenticationServiceH
#define AuthenticationServiceH
//---------------------------------------------------------------------------

#include "MainSession.h"
#include "DataModule.h"

class  AuthenticationService {

	private:
       	TDataModule1 *dataModule;
        MainSession *mainSession;

	public:
        AuthenticationService(MainSession *_mainSession, TDataModule1 *_dataModule);

    	bool loginUser(const UnicodeString& username, const UnicodeString& password);
        bool logoutUser();

        bool registerUser(const UnicodeString& username, const UnicodeString& password);

        void __fastcall (__closure *OnUsernameUnavailable)();
};

#endif
