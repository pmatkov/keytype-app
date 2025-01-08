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
	  void __fastcall TestcreateAbsolutePath();
	  void __fastcall TesttraverseUpDirTree();

};


void __fastcall TTestFileUtils::SetUp()
{
	LOGGER_LOG("Starting test...");
}

void __fastcall TTestFileUtils::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}

void __fastcall TTestFileUtils::TestcreateAbsolutePath()
{
	UnicodeString dirName = "Data";
	UnicodeString testPath = "C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\KeyType\\Data\\";

	LOGGER_LOG("Expected: " + testPath + "Result: " + FileUtils::createAbsolutePath(dirName, false));
	CheckEquals(testPath, FileUtils::createAbsolutePath(dirName, false), "Not the same path");
}

void __fastcall TTestFileUtils::TesttraverseUpDirTree()
{
	UnicodeString startingPath = "C:\\Program Files\\Test\\.";
	int level = 2;

    LOGGER_LOG("Starting path: " + startingPath + "New path (-" + IntToStr(level) + "): " + startingPath);
	startingPath = FileUtils::traverseUpDirTree(startingPath, level);

    UnicodeString testPath = "C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\KeyType\\Archiver\\Win32\\Debug";

    LOGGER_LOG("Test path: " + testPath + "Result: " + FileUtils::createAbsolutePath("Archiver", false) + "Win32\\Debug");
    CheckEquals(testPath, FileUtils::createAbsolutePath("Archiver", false) + "Win32\\Debug", "Not the same path");

}

static void registerTests()
{
  Testframework::RegisterTest(TTestFileUtils::Suite());
}
#pragma startup registerTests 33
