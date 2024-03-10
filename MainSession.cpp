//---------------------------------------------------------------------------

#pragma hdrstop

#include <chrono>
#include "MainSession.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

MainSession::MainSession() {
	LOGGER(LogLevel::Debug, "Main session created");
}

const User& MainSession::getUser() const {
	return user;
}
void MainSession::setUser(User _user) {
   user = _user;
   appSettings = AppSettings(user);
   typingSettings = TypingSettings(user);
}

AppSettings& MainSession::getAppSettings() {
	return appSettings;
}
void MainSession::setAppSettings(AppSettings _appSettings) {
   appSettings = _appSettings;
}

TypingSettings& MainSession::getTypingSettings() {
	return typingSettings;
}
void MainSession::setTypingSettings(TypingSettings _typingSettings) {
   typingSettings = _typingSettings;
}

const bool MainSession::isAuthenticated() const {
    return authenticated;
}

void MainSession::setAuthenticated(bool _authenticated) {
    authenticated = _authenticated;
}




