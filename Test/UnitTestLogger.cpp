//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitTestLogger.h"

UnitTestLogger::UnitTestLogger() {
    log = std::make_unique<TStringList>();
}


UnitTestLogger& UnitTestLogger::getLogger() {

    static UnitTestLogger logger;
    return logger;
}


void UnitTestLogger::addToLog(const UnicodeString& text) {

	log->Add(text);
};

void UnitTestLogger::clearLog() {

	log->Clear();
};

void UnitTestLogger::displayLog() {

    if (log->Count) {
    	ShowMessage(log->Text);
    }

}


//---------------------------------------------------------------------------
#pragma package(smart_init)
