//---------------------------------------------------------------------------

#pragma hdrstop

#include "Logger.h"


Logger::Logger()
{
	logStringList = new TStringList;
}

Logger::~Logger()
{
	delete logStringList;
}

TStringList* Logger::getLogStringList() const {

	return logStringList;

}

void Logger::log(const UnicodeString& text) {

	logStringList->Add(text);

};


//---------------------------------------------------------------------------
#pragma package(smart_init)
