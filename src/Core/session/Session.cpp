//---------------------------------------------------------------------------

#pragma hdrstop

#include "Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Session::Session() {
	startTime = std::chrono::system_clock::now();
}

void Session::startTimer() {
    startTime = std::chrono::system_clock::now();
}

void Session::stopTimer() {
    endTime = std::chrono::system_clock::now();
}

long Session::getElapsedTime() const {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count();
}


