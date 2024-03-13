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
        AppSettings appSettings;
        TypingSettings typingSettings;

	public:
        MainSession(AppSettings _appSettings, TypingSettings _typingSettings);

        AppSettings& getAppSettings();
		void setAppSettings(AppSettings _appSettings);

        TypingSettings& getTypingSettings();
		void setTypingSettings(TypingSettings _typingSettings);

};
#endif
