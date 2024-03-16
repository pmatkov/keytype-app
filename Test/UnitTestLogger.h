//---------------------------------------------------------------------------

#ifndef UnitTestLoggerH
#define UnitTestLoggerH

#include <memory>
#include <vcl.h>
#include <SysUtils.hpp>
#include <System.Classes.hpp>
#include <TestFramework.hpp>

#define LOGGER_LOG(message) UnitTestLogger::getLogger().addToLog(message)
#define LOGGER_DISPLAY_LOG() UnitTestLogger::getLogger().displayLog()

class UnitTestLogger
{
	private:
		std::unique_ptr<TStringList> log;

        UnitTestLogger();
        UnitTestLogger(const UnitTestLogger&)=delete;
   		UnitTestLogger& operator=(const UnitTestLogger&)=delete;

	public:
    	static UnitTestLogger& getLogger();
		void addToLog(const UnicodeString& text);
        void displayLog();

};


//---------------------------------------------------------------------------
#endif
