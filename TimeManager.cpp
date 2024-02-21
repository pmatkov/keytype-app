//---------------------------------------------------------------------------

#pragma hdrstop

#include "TimeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TimeManager::TimeManager() {
    startTime = std::chrono::system_clock::now();
}

void TimeManager::startTimer()  {
	startTime = std::chrono::system_clock::now();
}

void TimeManager::endTimer() {
	endTime = std::chrono::system_clock::now();
}

long TimeManager::getElapsedTime() const {

    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count();
}


UnicodeString TimeManager::getCurrentDate() {
    return FormatDateTime(L"yyyy-mm-dd", Now());
}


UnicodeString TimeManager::getCurrentDateTime() {
    return FormatDateTime(L"yyyy-mm-dd hh:nn:ss", Now());
}

