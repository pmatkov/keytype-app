//---------------------------------------------------------------------------

#pragma hdrstop

#include "AuthenticationService.h"
#include "User.h"
#include "ENullPointerException.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

AuthenticationService::AuthenticationService(MainSession *_mainSession) {

    if (_mainSession) {
       mainSession = _mainSession;
       LOGGER(LogLevel::Debug, "Authentication service created");
    }
    else {
        throw ENullPointerException();
    }
}

bool  AuthenticationService::loginUser(const UnicodeString& username) {

	if (username.Compare("guest") == 0) {

    	LOGGER(LogLevel::Info, "User logged in");

        mainSession->setUser(User());
		mainSession->setAuthenticated(true);
		return true;
	}

    return false;
}

bool  AuthenticationService::logoutUser() {

	if (mainSession->isAuthenticated()) {

    	LOGGER(LogLevel::Info, "User logged out");

        mainSession->setUser(User());
		mainSession->setAuthenticated(false);
		return true;
	}

    return false;
}

