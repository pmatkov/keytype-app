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
        bool userChanged = false;

	public:
        AuthenticationService(TDataModule1 *_dataModule);

    	bool loginUser(const UnicodeString& username, const UnicodeString& password);
        bool registerUser(const UnicodeString& username, const UnicodeString& password);

        bool logoutUser();

        const User& getUser() const;

        bool getUserChanged() const;
        void setUserChanged(bool _userChanged);

		bool verifyCredentials(const UnicodeString &username, const UnicodeString& hashedPassword, const UnicodeString& password);

        void __fastcall (__closure *OnUsernameUnavailable)();
};

#endif
