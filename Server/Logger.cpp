//---------------------------------------------------------------------------

#pragma hdrstop

#include "Logger.h"

#include <windows.h>
#include <memory>
#include <cstring>

#include <System.DateUtils.hpp>

#include "Logger.h"
#include "FileUtils.h"

#include "TimeManager.h"

#define LOG_PREFIX "server_"
#define DATE_FORMAT "yyyy-mm-dd"

//---------------------------------------------------------------------------
#pragma package(smart_init)


Logger::Logger() {
	intervalStart = std::chrono::steady_clock::now();
}

Logger& Logger::getLogger() {

    static Logger logger;
    return logger;
}

LogLevel operator|(LogLevel a, LogLevel b) {
    return static_cast<LogLevel>(static_cast<int>(a) | static_cast<int>(b));
}

LogLevel operator&(LogLevel a, LogLevel b) {
    return static_cast<LogLevel>(static_cast<int>(a) & static_cast<int>(b));
}

void Logger::setEnableLogging(bool _enableLogging) {
    enableLogging = _enableLogging;
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}


UnicodeString Logger::getLogLevelAsString(LogLevel level) {

	switch (level) {
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
			return  "UNKNOWN";
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

// add log to the buffer

 void Logger::log(const UnicodeString& message) {
 	buffer.push_back(message);
 }

void Logger::log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber) {

	const int MAX_LOGS = 10;

    if (static_cast<int>(logLevel) & static_cast<int>(level)) {

    	UnicodeString logLine;
        logLine = TimeManager::getCurrentDateTime() + " ";
        logLine += "[" + Logger::getLogLevelAsString(level) + "] ";
        logLine += UnicodeString(functionName) + ":" + IntToStr(lineNumber) + " - " + message;

        buffer.push_back(logLine);

        if (buffer.size() >= MAX_LOGS || std::chrono::steady_clock::now() - intervalStart >= flushInterval) {
            writeToFile();
        }
    }
}

// write log to file

void Logger::writeToFile() {

    if (!enableLogging) {
        return;
    }

    UnicodeString path = FileUtils::createAbsolutePath("Server\\Log\\" + UnicodeString(LOG_PREFIX) + TimeManager::getCurrentDate() + ".log", true);

    std::unique_ptr<TStreamWriter> writer;

    try {

        writer = std::make_unique<TStreamWriter>(path, true, TEncoding::UTF8, 1024);

        for (const UnicodeString &string: buffer) {
            writer->WriteLine(string);
        }

        buffer.clear();
        intervalStart = std::chrono::steady_clock::now();

    }
    catch (const Exception &ex)	{

        ShowMessage("Error writing to file: " + path);
    }

}

std::vector<UnicodeString> Logger::logLevelStrings = {"Debug", "Info", "Error", "Fatal", "All"};

std::vector<UnicodeString>& Logger::getLogLevelStrings() {
    return logLevelStrings;
}
