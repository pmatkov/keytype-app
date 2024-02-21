#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include "UnitTestLogger.h"
#include "Logger.h"

class TTestLogger : public TTestCase
{
public:
  __fastcall virtual TTestLogger(System::String name) : TTestCase(name) {}

  virtual void __fastcall SetUp();
  virtual void __fastcall TearDown();

__published:
	  void __fastcall TestgetLogLevelAsString();
	  void __fastcall TestcreateLogFileName();
      void __fastcall Testlog();

  private:
  	std::unique_ptr<UnitTestLogger> logger;

};


void __fastcall TTestLogger::SetUp()
{
	logger = std::make_unique<UnitTestLogger>();
	logger->log("Starting test...");
}

void __fastcall TTestLogger::TearDown()
{
	logger->log("Test completed.");

	if (logger)
	{
		if(logger->getLogStringList()->Count > 0)  {
			ShowMessage(logger->getLogStringList()->Text);
        }

	}
}

void __fastcall TTestLogger::TestgetLogLevelAsString()
{
 	LogLevel test = LogLevel::All;
	LogLevel compare = LogLevel::Info | LogLevel::Fatal;

	logger->log("Test: " + Logger::getLogLevelAsString(test));
	logger->log("Compare: " + Logger::getLogLevelAsString(compare));
	logger->log("Result: " + UnicodeString(test & compare ? "true" : "false"));

	CheckNotEquals(test, compare, "Same level");
}

void __fastcall TTestLogger::TestcreateLogFileName()
{
   	UnicodeString dirName = "Log";
	UnicodeString result = "";

	result = Logger::createLogFileName(dirName);
	logger->log("File name: " + result);

}

void __fastcall TTestLogger::Testlog()
{
   	UnicodeString dirName = "Log";
	UnicodeString result = "";

	LOGGER(LogLevel::Info, "message");
    LOGGER(LogLevel::Error, "error");

}


static void registerTests()
{
  Testframework::RegisterTest(TTestLogger::Suite());
}
#pragma startup registerTests 33
