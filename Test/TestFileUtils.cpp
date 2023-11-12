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
	  void __fastcall TestmoveUpDirTree();

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
	UnicodeString path = "WordList";
	UnicodeString expectedResult = "C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\WordList";

	logger->log("Starting path: " + path);
	path = FileUtils::createFilePath(path);
	logger->log("New path: " + path);

	UnicodeString substring = path.SubString(1, path.Length()/ 2);
	UnicodeString remainingSubstring = path.SubString(path.Length()/ 2 + 1, path.Length() - path.Length()/ 2 + 2);
	logger->log("First part: " + substring);
	logger->log("Remaining part: " + remainingSubstring);
	CheckTrue(path.Compare(expectedResult) == 0 , "Not correct path");
}
    
void __fastcall TTestFileUtils::TestmoveUpDirTree()
{
	UnicodeString path = "C:\\Program Files\\Test\\.";
	int level = 2;

	logger->log("Starting path: " + path);
	path = FileUtils::moveUpDirTree(path, level);
	logger->log("New path (-" + IntToStr(level) + "): " + path);

}
    


static void registerTests()
{
  Testframework::RegisterTest(TTestFileUtils::Suite());
}
#pragma startup registerTests 33
