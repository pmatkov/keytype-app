//---------------------------------------------------------------------------

#ifndef LoggerH
#define LoggerH
//---------------------------------------------------------------------------

#include <optional>
#include <vector>
#include <chrono>
#include <vcl.h>

#define LOGGER(level, message) Logger::getLogger().log(level, message, __FUNCTION__, __LINE__)
#define LOGGER_SIMPLE(messsage) Logger::getLogger().log(messsage)


enum class LogLevel {
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

        bool enableLogging = true;
        LogLevel logLevel = LogLevel::All;

        std::chrono::steady_clock::time_point intervalStart;
        const std::chrono::seconds flushInterval = std::chrono::seconds(60);

        static std::vector<UnicodeString> logLevelStrings;

        Logger();
        Logger(const Logger&)=delete;
   		Logger& operator=(const Logger&)=delete;

    public:

    	static Logger& getLogger();

        void setEnableLogging(bool _enableLogging);
    	void setLogLevel(LogLevel level);

        static UnicodeString getLogLevelAsString(LogLevel level);
        static LogLevel getStringAsLogLevel(const UnicodeString &level);

        void log(const UnicodeString& message);
        void log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber);
        void writeToFile();

       	static std::vector<UnicodeString>& getLogLevelStrings();

};

#endif
