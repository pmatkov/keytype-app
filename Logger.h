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

class MainSession;

enum class LogLevel {
    Debug = 1,
    Info = 2,
    Error = 4,
    Fatal = 8,
    All = Debug | Info | Error | Fatal,
    Count = 5,
    Unknown
};

enum class ArchiveLogLimit {
    Never,
    Auto,
    Week,
    Month,
    Count,
    Unknown
};

LogLevel operator|(LogLevel a, LogLevel b);
LogLevel operator&(LogLevel a, LogLevel b);

class Logger {

    private:
    	MainSession *mainSession;

    	std::vector<UnicodeString> buffer;

        UnicodeString logFilename = "";

        std::chrono::steady_clock::time_point intervalStart;
        const std::chrono::seconds flushInterval = std::chrono::seconds(60);

        static std::vector<UnicodeString> logLevelStrings;
        static std::vector<UnicodeString> archiveLogLimitStrings;

        Logger();
        Logger(const Logger&)=delete;
        Logger& operator=(const Logger&)=delete;

    public:
        void setMainSession(MainSession *_mainSession);
    	static Logger& getLogger();

        static UnicodeString getLogLevelAsString(LogLevel level);
        static LogLevel getStringAsLogLevel(const UnicodeString &level);

        void log(const UnicodeString& logEntry);
        void log(LogLevel level, const UnicodeString& message, const char* functionName, int lineNumber);
        void writeToFile();

        UnicodeString findNextFileIndex(const UnicodeString &dirName, const UnicodeString &fileType);
        UnicodeString getFileIndex(const UnicodeString &file);
        TDate convertLogTimeStampToDate(const UnicodeString &log);
        void sortLogsByTimeStamp(std::vector<UnicodeString> &logs, bool sortDescending);

        std::vector<UnicodeString> findMatchingLogs(std::vector<UnicodeString> logs, ArchiveLogLimit archiveLogLimit);
        UnicodeString archiveLogFiles();

       	static std::vector<UnicodeString>& getLogLevelStrings();
        static std::vector<UnicodeString>& getArchiveLogLimitStrings();
};

#endif
