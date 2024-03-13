//---------------------------------------------------------------------------

#ifndef AuthenticationServiceH
#define AuthenticationServiceH
//---------------------------------------------------------------------------

#include "MainSession.h"
#include "DataModule.h"

class  AuthenticationService {

	private:
       	TDataModule1 *dataModule;

        User user;
        bool authenticated = false;

	public:
        AuthenticationService(TDataModule1 *_dataModule);

    	bool loginUser(const UnicodeString& username, const UnicodeString& password);
        bool logoutUser();
        bool registerUser(const UnicodeString& username, const UnicodeString& password);
        const User& getUser() const;

        void __fastcall (__closure *OnUsernameUnavailable)();
};

#endif
