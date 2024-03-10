//---------------------------------------------------------------------------

#ifndef LoggerH
#define LoggerH
//---------------------------------------------------------------------------

#include <vector>
#include <chrono>
#include <mutex>
#include <vcl.h>

#define SECONDS 60
#define LOGGER(level, message) Logger::log(level, message, __FUNCTION__, __LINE__)

enum LogLevel {
    Debug = 1,
    Info = 2,
    Error = 4,
    Fatal = 8,
    All = Debug | Info | Error | Fatal,
    Count = 5,
    Unknown
};

LogLevel operator|(LogLevel a, LogLevel b);
LogLevel operator&(LogLevel a, LogLevel b);

class Logger {

    private:
    	static std::vector<UnicodeString> buffer;
        static UnicodeString logFilename;
        static bool firstFlush;
        static LogLevel logLevel;

        static std::chrono::steady_clock::time_point lastFlushTime;
        static const std::chrono::seconds flushInterval;
        static std::mutex bufferMutex;

        static std::vector<UnicodeString> logLevelStrings;

        Logger() {}

    public:
    	static void setLogLevel(LogLevel level);
        static UnicodeString getLogLevelAsString(LogLevel level);
        static LogLevel getStringAsLogLevel(const UnicodeString &level);

        static UnicodeString createLogFileName(const UnicodeString& dirName);

        static void log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber);
        static void flushBuffer();
        static void registerFlushOnExit();

        static std::vector<UnicodeString>& getLogLevelStrings();
};

#endif
