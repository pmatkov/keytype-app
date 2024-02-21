//---------------------------------------------------------------------------

#ifndef MainSessionH
#define MainSessionH
//---------------------------------------------------------------------------
#include "User.h"
#include "Session.h"
#include "Settings.h"

class MainSession : public Session {

	private:
		User user;
        Settings settings;
        bool authenticated = false;

	public:
        MainSession();
        MainSession(User _user, Settings _settings);

    	const User& getUser() const;
		void setUser(User _user);

        const Settings& getSettings() const;
		void setSettings(Settings settings);

        const bool isAuthenticated() const;
        void setAuthenticated(bool _authenticated);

};
#endif
