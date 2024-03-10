//---------------------------------------------------------------------------

#pragma hdrstop

#include <memory>
#include "Logger.h"
#include "FileUtils.h"
#include "TimeManager.h"
#include "EnumUtils.h"

#define MAX_BUFFER_SIZE 20

//---------------------------------------------------------------------------
#pragma package(smart_init)

LogLevel operator|(LogLevel a, LogLevel b) {
    return static_cast<LogLevel>(static_cast<int>(a) | static_cast<int>(b));
}

LogLevel operator&(LogLevel a, LogLevel b) {
    return static_cast<LogLevel>(static_cast<int>(a) & static_cast<int>(b));
}

std::vector<UnicodeString> Logger::buffer;
UnicodeString Logger::logFilename = "";
LogLevel Logger::logLevel = LogLevel::All;

std::chrono::steady_clock::time_point Logger::lastFlushTime = std::chrono::steady_clock::now();
const std::chrono::seconds Logger::flushInterval = std::chrono::seconds(SECONDS);
std::mutex Logger::bufferMutex;

bool Logger::firstFlush = true;

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}


UnicodeString Logger::getLogLevelAsString(LogLevel level) {

    switch(level) {
        case LogLevel::Debug:
            return  "DEBUG";
            break;
        case LogLevel::Info:
            return "INFO";
            break;
        case LogLevel::Error:
            return  "ERROR";
            break;
        case LogLevel::Fatal:
            return  "FATAL";
            break;
        case LogLevel::All:
            return "ALL";
            break;
        default:
        	return  "Unknown";
    }
}

LogLevel Logger::getStringAsLogLevel(const UnicodeString &level) {

   if (level.UpperCase() == "DEBUG") {
        return LogLevel::Debug;
    } else if (level.UpperCase() == "INFO") {
        return LogLevel::Info;
    } else if (level.UpperCase() == "ERROR") {
        return LogLevel::Error;
    } else if (level.UpperCase() == "FATAL") {
        return LogLevel::Fatal;
    } else if (level.UpperCase() == "ALL") {
        return LogLevel::All;
    } else {
    	return LogLevel::Unknown;
    }

}

// creates log file name of the format yyyy-mm-dd-ab.log where ab
// is numerical index (e.g. "2024-01-20-00.log")
UnicodeString Logger::createLogFileName(const UnicodeString &dirName) {

	UnicodeString dirPath = FileUtils::createAbsolutePath("Log", false);
    std::optional<std::vector<UnicodeString>> filenames = FileUtils::getFileNames(dirPath, "log");

    UnicodeString indexA = "0";
    UnicodeString indexB = "0";

     if (filenames.has_value()) {

    	int next = 0, max = 0;
        bool noMatch = true;

        for (const UnicodeString &fname : *filenames) {

           if ((fname.SubString(1, 10)).Compare(TimeManager::getCurrentDate()) == 0) {

           		noMatch = false;

                int a = StrToInt(fname.SubString(12, 1));
                int b = StrToInt(fname.SubString(13, 1));

                int current = (a * 10) + b;

                if (current > max) {
                    max = current;
                }
           }

           if ((max == 0 || max == 99) && noMatch) {
              next = 0;
           }
           else  {
              next = max + 1;
           }

        }
        indexA = IntToStr(next/ 10);
        indexB = IntToStr(next % 10);
     }
    return TimeManager::getCurrentDate() + '-' + indexA + indexB;
}


// add log to buffer
void Logger::log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber) {



    if (logLevel & level) {

    	UnicodeString logLine;
        logLine = TimeManager::getCurrentDateTime() + " ";
          logLine += "[" + Logger::getLogLevelAsString(level) + "] ";
          logLine += UnicodeString(functionName) + ":" + IntToStr(lineNumber) + " - " + message;

        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            buffer.push_back(logLine);
        }

        if (buffer.size() >= MAX_BUFFER_SIZE || std::chrono::steady_clock::now() - lastFlushTime >= flushInterval) {
            flushBuffer();
            firstFlush = false;
        }
    }
}

// write log to file

void Logger::flushBuffer() {

    std::lock_guard<std::mutex> lock(bufferMutex);

    UnicodeString path = FileUtils::createAbsolutePath("Log\\" + TimeManager::getCurrentDate() + ".log", true);

    std::unique_ptr<TStreamWriter> writer;

    try {

        writer = std::make_unique<TStreamWriter>(path, true, TEncoding::UTF8, 1024);

        if (firstFlush) {
        	writer->WriteLine(UnicodeString("***"));
        }

        for (const UnicodeString &string: buffer){
            writer->WriteLine(string);
        }

        buffer.clear();

    }
    catch (const Exception &ex)	{

        ShowMessage("Error writing to file: " + path);
    }

}

// write log on app close

void Logger::registerFlushOnExit() {

	atexit(flushBuffer);
}

std::vector<UnicodeString>& Logger::getLogLevelStrings() {
    return logLevelStrings;
}

std::vector<UnicodeString> Logger::logLevelStrings = {"Debug", "Info", "Error", "Fatal", "All"};
