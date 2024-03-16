#include <System.hpp>
#pragma hdrstop

#include <optional>
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

        void __fastcall TestConvertLogTimeStampToDate();
        void __fastcall TestSortLogsByTimeStamp();
        void __fastcall TestFindMatchingLogs();
        void __fastcall TestGetFileIndex();
        void __fastcall TestFindNextFileIndex();
        void __fastcall TestArchiveLogFiles();

    private:
    	Logger *logger;

};


void __fastcall TTestLogger::SetUp()
{
 	logger = &(Logger::getLogger());
	LOGGER_LOG("Starting test...");
}

void __fastcall TTestLogger::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}

void __fastcall TTestLogger::TestgetLogLevelAsString()
{
	LOGGER_LOG("Expected: INFO Result: " + Logger::getLogLevelAsString(LogLevel::Info));
    LOGGER_LOG("Expected: UNKNOWN Result: " + Logger::getLogLevelAsString(LogLevel::Info | LogLevel::Fatal));

    CheckEquals("INFO", Logger::getLogLevelAsString(LogLevel::Info), "Wrong conversion of LogLevel");
    CheckEquals("UNKNOWN", Logger::getLogLevelAsString(LogLevel::Info | LogLevel::Fatal), "Wrong conversion of LogLevel");
}

void __fastcall TTestLogger::TestConvertLogTimeStampToDate()
{
    TFormatSettings formatSettings = {.ShortDateFormat = "yyyy-mm-dd"};
    UnicodeString date = "2024-03-14";

    // test valid date

    Check(StrToDate(date, formatSettings) == logger->convertLogTimeStampToDate("ktype_log_2024-03-14_01"), "Wrong conversion of date value");

	LOGGER_LOG("Expected: " +  date + " Result: " + DateToStr(logger->convertLogTimeStampToDate("ktype_log_2024-03-14"), formatSettings));

    // test invalid date

    try {
        TDate dt = logger->convertLogTimeStampToDate("ktype_log_20-03-14");
        Check(false, "Exception not thrown");
        LOGGER_LOG("Exception not thrown");

    } catch (Exception &ex) {
        Check(ex.Message == "Invalid argument exception", "Unknown exception message");
    	LOGGER_LOG("Exception message: " + ex.Message);
    }
}

void __fastcall TTestLogger::TestSortLogsByTimeStamp()
{
    std::vector<UnicodeString> testLogs = { "ktype_log_2024-03-14", "ktype_log_2024-02-03", "ktype_log_2024-02-01", "ktype_log_2024-02-02"};

    // test ascending
    logger->sortLogsByTimeStamp(testLogs, false);

    LOGGER_LOG("Expected: ktype_log_2024-02-01, ktype_log_2024-02-02, ktype_log_2024-02-03, ktype_log_2024-03-14");

    int i = 0;
    for (const UnicodeString &log : testLogs) {
    	LOGGER_LOG("Result: log[" + IntToStr(i++) + "] " +  log);
    }

    CheckEquals(testLogs[0], "ktype_log_2024-02-01", "Logs not sorted correctly");
    CheckEquals(testLogs[3], "ktype_log_2024-03-14", "Logs not sorted correctly");
}


void __fastcall TTestLogger::TestFindMatchingLogs()
{
    std::vector<UnicodeString> testLogs = { "ktype_log_2024-03-14", "ktype_log_2024-03-05", "ktype_log_2023-12-11", "ktype_log_2024-03-11",  "ktype_log_2023-11-05", "ktype_log_2024-01-01", "ktype_log_2024-03-07"};

    std::vector<UnicodeString> resultLogs = logger->findMatchingLogs(testLogs, LogInterval::Weekly);

    Check(resultLogs.size(), "No matching logs");
    logger->sortLogsByTimeStamp(resultLogs, false);

    LOGGER_LOG("Expected: ktype_log_2023-11-05, ktype_log_2023-12-11, ktype_log_2024-01-01, ktype_log_2024-03-05, ktype_log_2024-03-07");

    int i = 0;
    for (const UnicodeString &log : resultLogs) {
    	LOGGER_LOG("Result: log[" + IntToStr(i++) + "] " +  log);
    }

    CheckEquals(resultLogs[0], "ktype_log_2023-11-05", "Logs not filtered correctly");
    CheckEquals(resultLogs[1], "ktype_log_2023-12-11", "Logs not filtered  correctly");

    resultLogs = logger->findMatchingLogs(testLogs, LogInterval::Auto);
    Check(resultLogs.size(), "No matching logs");
    logger->sortLogsByTimeStamp(resultLogs, false);

    LOGGER_LOG("Expected: ktype_log_2023-11-05, ktype_log_2023-12-11, ktype_log_2024-01-01, ktype_log_2024-03-05, ktype_log_2024-03-07");

    i = 0;
    for (const UnicodeString &log : resultLogs) {
    	LOGGER_LOG("Result: log[" + IntToStr(i++) + "] " +  log);
    }

    CheckEquals(resultLogs[0], "ktype_log_2023-11-05", "Logs not filtered correctly");
}

void __fastcall TTestLogger::TestGetFileIndex()
{
    UnicodeString testLog = "ktype_log_2024-03-14_00";

    // test valid index

    Check("00" == logger->getFileIndex(testLog), "Wrong file index");

	LOGGER_LOG("Expected: 00 Result: " + logger->getFileIndex(testLog));

    // test invalid index

    try {
        std::optional<UnicodeString> index = logger->getFileIndex("ktype_log_20-03-14_00");
        Check(false, "Exception not thrown");
        LOGGER_LOG("Exception not thrown");

    } catch (Exception &ex) {
      	LOGGER_LOG("Exception message: " + ex.Message);
        Check(ex.Message == "Invalid argument exception", "Unknown exception message");
    }
}

void __fastcall TTestLogger::TestFindNextFileIndex()
{
    // test valid index

    LOGGER_LOG("Expected: 00 Result: " + logger->findNextFileIndex("Log", "zip"));
    Check("00" == logger->findNextFileIndex("Log", "zip"), "Wrong file index");
}


void __fastcall TTestLogger::TestArchiveLogFiles()
{
    // test archiving

    LOGGER_LOG("Expected: true Result: " + (logger->archiveLogFiles(LogInterval::Auto) ? UnicodeString("true") :  UnicodeString("false")));
    CheckEquals(true, logger->archiveLogFiles(LogInterval::Auto), "Wrong file index");
}


static void registerTests()
{
  Testframework::RegisterTest(TTestLogger::Suite());
}
#pragma startup registerTests 33
