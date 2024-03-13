//---------------------------------------------------------------------------

#pragma hdrstop

#include "Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Session::Session() {
	sessionStart = std::chrono::system_clock::now();
    sessionUuid = UUIDGenerator::generateUUID();
}

void Session::setSessionStart() {
    sessionStart = std::chrono::system_clock::now();
}

void Session::setSessionEnd() {
    sessionEnd = std::chrono::system_clock::now();
}

long Session::getElapsedTime() const {

    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - sessionStart).count();
}


