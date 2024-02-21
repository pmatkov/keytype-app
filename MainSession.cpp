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
MainSession::MainSession(User _user, Settings _settings) : user(_user), settings(_settings) {
	LOGGER(LogLevel::Debug, "Main session created");
}

const User& MainSession::getUser() const {
	return user;
}
void MainSession::setUser(User _user) {
   user = _user;
}

 const Settings& MainSession::getSettings() const {
	return settings;
}
void MainSession::setSettings(Settings _settings) {
   settings = _settings;
}

const bool MainSession::isAuthenticated() const {
    return authenticated;
}

void MainSession::setAuthenticated(bool _authenticated) {
    authenticated = _authenticated;
}




