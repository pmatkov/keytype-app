//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <vector>
#include <memory>
#include <System.hpp>


#include "AchievementsUtils.h"
#include "AchievementsHeader.h"
#include "AchievementsRecord.h"
#include "FileUtils.h"
#include "CryptoUtils.h"

#include "UnitTestLogger.h"

class TTestAchievementsUtils : public TTestCase
{
public:
	  __fastcall virtual TTestAchievementsUtils(System::String name) : TTestCase(name) {}
	  virtual void __fastcall SetUp();
	  virtual void __fastcall TearDown();

__published:
	  void __fastcall TestsaveToFile();
      void __fastcall TestreadFromFile();
};

void __fastcall TTestAchievementsUtils::SetUp()
{
	LOGGER_CLEAR_LOG();
	LOGGER_LOG("Starting test...");
}

void __fastcall TTestAchievementsUtils::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}

void __fastcall TTestAchievementsUtils::TestsaveToFile()
{

    AchievementsHeader header("AcmFile", 1.0, 2);
    UnicodeString hash = CryptoUtils::generateSHA512Hash(header);
    header.setHashValue(hash);

    std::vector<AchievementsRecord> records = {
       { 1, "Beginner", "First lesson completed", TDateTime(2024, 2, 1) },
       { 1, "SpeedMaster", "New speed record", TDateTime::CurrentDate() }
    };

    AchievementsUtils::saveToFile(header, records, FileUtils::createAbsolutePath("Data\\test", true));
    LOGGER_LOG("Result: " + hash);
}

void __fastcall TTestAchievementsUtils::TestreadFromFile()
{

    std::vector<AchievementsRecord> records = AchievementsUtils::readFromFile(FileUtils::createAbsolutePath("Data\\test", true));

    if (records.size()) {
       	LOGGER_LOG("Records size: " + IntToStr(static_cast<int>(records.size())) + " record 1: " + records[0]);
    }
    else {
         LOGGER_LOG("No records");
    }


}

static void registerTests()
{
  Testframework::RegisterTest(TTestAchievementsUtils::Suite());
}
#pragma startup registerTests 33
