//---------------------------------------------------------------------------

#pragma hdrstop

#include <chrono>
#include "MainSession.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

MainSession::MainSession(AppSettings _appSettings, TypingSettings _typingSettings) {

   appSettings = _appSettings;
   typingSettings = _typingSettings;

   LOGGER(LogLevel::Debug, "Main session created");
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




