//---------------------------------------------------------------------------

#ifndef LoggerH
#define LoggerH
//---------------------------------------------------------------------------

#include <optional>
#include <vector>
#include <chrono>
#include <vcl.h>

#define LOGGER(level, message) Logger::getLogger().log(level, message, __FUNCTION__, __LINE__)


enum class LogLevel {
    Debug = 1,
    Info = 2,
    Error = 4,
    Fatal = 8,
    All = Debug | Info | Error | Fatal,
    Count = 5,
    Unknown
};

enum class LogInterval {
    Never,
    Auto,
    Weekly,
    Monthly,
    Count,
    Unknown
};

LogLevel operator|(LogLevel a, LogLevel b);
LogLevel operator&(LogLevel a, LogLevel b);

class Logger {

    private:
    	std::vector<UnicodeString> buffer;

        UnicodeString logFilename = "";
        bool firstFlush = true;

        bool enableLogging = false;
        LogLevel logLevel = LogLevel::All;
        LogInterval logInterval = LogInterval::Auto;

        std::chrono::steady_clock::time_point intervalStart;
        const std::chrono::seconds flushInterval = std::chrono::seconds(60);

        static std::vector<UnicodeString> logLevelStrings;
        static std::vector<UnicodeString> logIntervalStrings;

        Logger();
        Logger(const Logger&)=delete;
   		Logger& operator=(const Logger&)=delete;

    public:

    	static Logger& getLogger();

        void setEnableLogging(bool _enableLogging);
    	void setLogLevel(LogLevel level);
        LogInterval getLogInterval() const;
        void setLogInterval(LogInterval _logInterval);

        static UnicodeString getLogLevelAsString(LogLevel level);
        static LogLevel getStringAsLogLevel(const UnicodeString &level);

        void log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber);
        void flushBuffer();

        UnicodeString findNextFileIndex(const UnicodeString &dirName, const UnicodeString &fileType);
        UnicodeString getFileIndex(const UnicodeString &file);
        TDate convertLogTimeStampToDate(const UnicodeString &log);
        void sortLogsByTimeStamp(std::vector<UnicodeString> &logs, bool sortDescending);

        std::vector<UnicodeString> findMatchingLogs(std::vector<UnicodeString> logs, LogInterval interval);
        bool archiveLogFiles(LogInterval interval);

       	static std::vector<UnicodeString>& getLogLevelStrings();
        static std::vector<UnicodeString>& getLogIntervalStrings();
};

#endif
