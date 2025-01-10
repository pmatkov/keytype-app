#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <memory>

#include "FileUtils.h"
#include "UnitTestLogger.h"


class TTestFileUtils : public TTestCase
{
public:
	  __fastcall virtual TTestFileUtils(System::String name) : TTestCase(name) {}
	  virtual void __fastcall SetUp();
	  virtual void __fastcall TearDown();
  
__published:
	  void __fastcall TestgetProjectDirPath();
	  void __fastcall TestcreateProjectSubDirPath();
	  void __fastcall TestcreateStepUpDirPath();

};


void __fastcall TTestFileUtils::SetUp()
{
	LOGGER_CLEAR_LOG();
	LOGGER_LOG("Starting test...");
}

void __fastcall TTestFileUtils::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}


void __fastcall TTestFileUtils::TestgetProjectDirPath()
{
	UnicodeString testPath = "C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\KeyType\\";
	UnicodeString resultPath = FileUtils::getProjectDirPath(4);

	LOGGER_LOG("Expected: " + testPath);
	LOGGER_LOG("Result: " + resultPath);
	CheckEquals(testPath, resultPath, "Not the same path");
}

void __fastcall TTestFileUtils::TestcreateProjectSubDirPath()
{
	UnicodeString testPath = "C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\KeyType\\Data\\";
	UnicodeString resultPath = FileUtils::createProjectSubDirPath("Data", 4);

	LOGGER_LOG("Expected: " + testPath);
	LOGGER_LOG("Result: " + resultPath);
	CheckEquals(testPath, resultPath, "Not the same path");
}

void __fastcall TTestFileUtils::TestcreateStepUpDirPath()
{

	UnicodeString testPath = "C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\Data\\..\\";
	UnicodeString resultPath = FileUtils::createStepUpDirPath("C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\Data", 1);

	LOGGER_LOG("Expected: " + testPath);
	LOGGER_LOG("Result: " + resultPath);
	CheckEquals(testPath, resultPath, "Not the same path");

}

static void registerTests()
{
  Testframework::RegisterTest(TTestFileUtils::Suite());
}
#pragma startup registerTests 33
