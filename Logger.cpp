//---------------------------------------------------------------------------

#pragma hdrstop

#undef UNICODE
#define UNICODE

#include <windows.h>
#include <memory>
#include <cstring>

#include <System.DateUtils.hpp>

#include "Logger.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "EnumUtils.h"

#include "TimeManager.h"
#include "EDirNotFoundException.h"
#include "EInvalidArgumentException.h"
#include "ENullPointerException.h"


#define LOG_PREFIX "keytype_"
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

LogInterval Logger::getLogInterval() const {
    return logInterval;
}


void Logger::setLogInterval(LogInterval _logInterval) {
    logInterval = _logInterval;
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


// add log to buffer
void Logger::log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber) {

	const int MAX_LOGS = 20;

    if (enableLogging && (static_cast<int>(logLevel) & static_cast<int>(level))) {

    	UnicodeString logLine;
        logLine = TimeManager::getCurrentDateTime() + " ";
        logLine += "[" + Logger::getLogLevelAsString(level) + "] ";
        logLine += UnicodeString(functionName) + ":" + IntToStr(lineNumber) + " - " + message;

        buffer.push_back(logLine);

        if (buffer.size() >= MAX_LOGS || std::chrono::steady_clock::now() - intervalStart >= flushInterval) {
            flushBuffer();
            firstFlush = false;
        }
    }
}

// write log to file

void Logger::flushBuffer() {

    if (!enableLogging) {
        return;
    }

    UnicodeString path = FileUtils::createAbsolutePath("Log\\" + UnicodeString(LOG_PREFIX) + TimeManager::getCurrentDate() + ".log", true);

    std::unique_ptr<TStreamWriter> writer;

    try {

        writer = std::make_unique<TStreamWriter>(path, true, TEncoding::UTF8, 1024);

        if (firstFlush) {
        	writer->WriteLine(UnicodeString("!--Session started--!"));
            firstFlush = false;
        }

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

std::vector<UnicodeString> Logger::logIntervalStrings = {"Never", "Auto", "Weekly", "Monthly"};

std::vector<UnicodeString>& Logger::getLogIntervalStrings() {
    return logIntervalStrings;
}

UnicodeString Logger::findNextFileIndex(const UnicodeString &dirName, const UnicodeString &fileType) {

    std::optional<std::vector<UnicodeString>> files;
    UnicodeString dirPath = FileUtils::createAbsolutePath(dirName, false);

    try {
        files = FileUtils::getFileNames(dirPath, fileType);
    } catch (CustomExceptions::EDirNotFoundException &ex) {
         throw Exception("Dir not found");
    }

    UnicodeString index = "00";

     if (files.has_value()) {

    	int max = 0, idx = 0;
        bool match = false;

        for (const UnicodeString &file : *files) {

            if (convertLogTimeStampToDate(file) == static_cast<TDate>(Date())) {

            	UnicodeString strIndex = getFileIndex(file);

                if (strIndex.Length() == 2) {
                  idx = (StrToInt(strIndex[1]) * 10) + StrToInt(strIndex[2]);
                }

                if (idx > max) {
                    max = idx;
                }
                match = true;
            }
        }
        if (match) {
        	index[1] = (max + 1)/ 10 + '0';
        	index[2] = (max + 1)% 10 + '0';
        }
     }
     return index;
}


std::vector<UnicodeString> Logger::findMatchingLogs(std::vector<UnicodeString> logs, LogInterval interval) {

    const int MAX_LOG_FILES = 10;

    std::vector<UnicodeString> matchingLogs;

    if (interval == LogInterval::Auto && logs.size() > MAX_LOG_FILES) {

        sortLogsByTimeStamp(logs, false);

        for (int i = 0; i < MAX_LOG_FILES; i++) {
            matchingLogs.push_back(logs[i]);
        }
    }
    else {

        for (const UnicodeString &log: logs) {

            TDate logDate = convertLogTimeStampToDate(log);

            int days = DaysBetween(logDate, Now());

            if (interval == LogInterval::Weekly && days >= 7) {
                matchingLogs.push_back(log);
            }
            else if (interval == LogInterval::Monthly && days >= 30) {
                matchingLogs.push_back(log);
            }
        }
    }

    return matchingLogs;
}

void Logger::sortLogsByTimeStamp(std::vector<UnicodeString> &logs, bool sortDescending) {

	bool swap;

    do {
    	swap = false;

    	for (int i = 0; i < logs.size() - 1; i++) {

        	TDate dt1 = convertLogTimeStampToDate(logs[i]);
            TDate dt2 = convertLogTimeStampToDate(logs[i+1]);

            if ((sortDescending && dt1 < dt2) || (!sortDescending && dt1 > dt2)) {
            	UnicodeString temp = logs[i];
            	logs[i] = logs[i+1];
            	logs[i+1] = temp;
                swap = true;
            }
    	}
    } while (swap);

}

TDate Logger::convertLogTimeStampToDate(const UnicodeString &log) {

	UnicodeString logDateString = "", expectedFormat = "dddd-dd-dd", detectedFormat = "";
    TFormatSettings formatSettings = {.ShortDateFormat = "yyyy-mm-dd"};
    int count = 0;

        for (const wchar_t &ch: log) {
            if (isdigit(ch) || ch == L'-') {
               logDateString += ch;
               detectedFormat += isdigit(ch) ? L'd' : ch;
               count++;
            }
            if (count == expectedFormat.Length()) {
                  break;
            }
        }

    if (expectedFormat == detectedFormat) {
    	return StrToDate(logDateString, formatSettings);
    }
    else {
    	throw CustomExceptions::EInvalidArgumentException();
    }
}


UnicodeString Logger::getFileIndex(const UnicodeString &file) {

	UnicodeString expectedFormat = "dddd-dd-dd";

    int start = 1, end = 1;
    bool detectedNumbers = false;

    for (int i = 1; i <= file.Length(); i++) {

    	if (isdigit(file[i])) {

            if (!detectedNumbers) {
            	start = i;
            	detectedNumbers = true;
            }
            end = i;
        }
    }

    UnicodeString timeStamp = file.SubString(start, end - start + 1);

    if (timeStamp.Length() == expectedFormat.Length() + 3) {
        return  timeStamp.SubString(timeStamp.Length()-1, 2);
    }
    else {
    	throw CustomExceptions::EInvalidArgumentException();
    }
}

bool Logger::archiveLogFiles(LogInterval interval)
{

    if (!enableLogging) {
       return false;
    }
    // find log files
	std::optional<std::vector<UnicodeString>> logs;
	UnicodeString dirPath = FileUtils::createAbsolutePath("Log", false);

    try {
        logs = FileUtils::getFileNames(dirPath, "log");
    } catch (CustomExceptions::EDirNotFoundException &ex) {
         throw Exception("Log dir not found");
    }

    std::vector<UnicodeString> matchingLogs;

    if (logs.has_value()) {
        matchingLogs = findMatchingLogs(*logs, interval);
    }

    if (matchingLogs.size()) {

    	UnicodeString index = findNextFileIndex("Log", "tgz");
		UnicodeString command =	FileUtils::createAbsolutePath("Archiver", false) + "Win32\\Debug\\Archiver.exe tar -czf " + \
         FileUtils::createAbsolutePath("Log", false) + "archive_" + TimeManager::getCurrentDate() +  "_" + index + ".tgz -C " + \
         FileUtils::createAbsolutePath("Log", false) + " " + TextUtils::vectorToString(matchingLogs);

        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        unsigned long returnValue;

        if (!CreateProcess(NULL, command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            LOGGER(LogLevel::Error, "Unable to create process");
            return false;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &returnValue);
        LOGGER(LogLevel::Info, "Process return value: " +  IntToStr((int)(returnValue)));

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

    }

    return true;

}

