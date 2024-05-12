//---------------------------------------------------------------------------

#pragma hdrstop

#include "Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Session::Session() {
	sessionStartTime = std::chrono::system_clock::now();
}

void Session::startSessionTimer() {
    sessionStartTime = std::chrono::system_clock::now();
}

void Session::stopSessionTimer() {
    sessionEndTime = std::chrono::system_clock::now();
}

long Session::getElapsedTime() const {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - sessionStartTime).count();
}


