//---------------------------------------------------------------------------

#pragma hdrstop

#include "LoginManager.h"
#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void LoginManager::setSessionModule(SessionModule *_sessionModule) {

	if (_sessionModule) {
	   sessionModule = _sessionModule;
	}

}


bool LoginManager::isValidLogin(const UnicodeString& input) {

	if (input.Compare("guest") == 0) {

		sessionModule->getSession()->setUser(User("guest", true));
		return true;
	}

    return false;

}

