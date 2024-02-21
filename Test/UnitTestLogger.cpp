//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitTestLogger.h"


UnitTestLogger::UnitTestLogger()
{
	logList = new TStringList;
}

UnitTestLogger::~UnitTestLogger()
{
	delete logList;
}

TStringList* UnitTestLogger::getLogStringList() const {

	return logList;

}

void UnitTestLogger::log(const UnicodeString& text) {

	logList->Add(text);

};


//---------------------------------------------------------------------------
#pragma package(smart_init)
