#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>

#include "FileUtils.h"
#include "Logger.h"

class TTestFileUtils : public TTestCase
{
public:
	  __fastcall virtual TTestFileUtils(System::String name) : TTestCase(name) {}
	  virtual void __fastcall SetUp();
	  virtual void __fastcall TearDown();
  
__published:
	  void __fastcall TestcreateFilePath();
	  void __fastcall TesttraverseUpDirTree();

  private:
		Logger* logger;
};


void __fastcall TTestFileUtils::SetUp()
{
	logger = new Logger;
	logger->log("Starting test...");
}

void __fastcall TTestFileUtils::TearDown()
{
	logger->log("Test completed.");

	if (logger)
	{
		if(logger->getLogStringList()->Count > 0)
			ShowMessage(logger->getLogStringList()->Text);

	  	delete logger;
	}
}

void __fastcall TTestFileUtils::TestcreateFilePath()
{
	UnicodeString dirName = "Data";
	UnicodeString reference = "C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\KeyType\\Data\\";
	UnicodeString result = "";

	logger->log("Expected path: " + reference);
	result = FileUtils::createFilePath(dirName);
	logger->log("New path: " + result);

	CheckEquals(reference, result, "Not the same path");
}
    
void __fastcall TTestFileUtils::TesttraverseUpDirTree()
{
	UnicodeString path = "C:\\Program Files\\Test\\.";
	int level = 2;

	logger->log("Starting path: " + path);
	path = FileUtils::traverseUpDirTree(path, level);
	logger->log("New path (-" + IntToStr(level) + "): " + path);

}
    


static void registerTests()
{
  Testframework::RegisterTest(TTestFileUtils::Suite());
}
#pragma startup registerTests 33
