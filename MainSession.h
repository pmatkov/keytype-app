//---------------------------------------------------------------------------

#ifndef MainSessionH
#define MainSessionH
//---------------------------------------------------------------------------
#include "User.h"
#include "Session.h"
#include "AppSettings.h"
#include "TypingSettings.h"
//---------------------------------------------------------------------------

class MainSession : public Session {

	private:
		User user;
        AppSettings appSettings;
        TypingSettings typingSettings;
        bool authenticated = false;

	public:
        MainSession();

    	const User& getUser() const;
		void setUser(User _user);

        AppSettings& getAppSettings();
		void setAppSettings(AppSettings _appSettings);

        TypingSettings& getTypingSettings();
		void setTypingSettings(TypingSettings _typingSettings);

        const bool isAuthenticated() const;
        void setAuthenticated(bool _authenticated);

};
#endif
