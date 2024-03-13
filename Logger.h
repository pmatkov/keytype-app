//---------------------------------------------------------------------------

#ifndef LoggerH
#define LoggerH
//---------------------------------------------------------------------------

#include <vector>
#include <chrono>
#include <vcl.h>

#define LOGGER(level, message) Logger::getLogger().log(level, message, __FUNCTION__, __LINE__)

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
    	std::vector<UnicodeString> buffer;
        UnicodeString logFilename = "";
        bool firstFlush = true;
        LogLevel logLevel = LogLevel::All;

        std::chrono::steady_clock::time_point intervalStart;
        const std::chrono::seconds flushInterval = std::chrono::seconds(60);

        static std::vector<UnicodeString> logLevelStrings;

        Logger();
        Logger(const Logger&)=delete;
   		Logger& operator=(const Logger&)=delete;

    public:

    	static Logger& getLogger();
    	void setLogLevel(LogLevel level);

        static UnicodeString getLogLevelAsString(LogLevel level);
        static LogLevel getStringAsLogLevel(const UnicodeString &level);

        UnicodeString createLogFileName(const UnicodeString& dirName);

        void log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber);
        void flushBuffer();

       	static std::vector<UnicodeString>& getLogLevelStrings();
};

#endif
