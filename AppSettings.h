//---------------------------------------------------------------------------

#ifndef AppSettingsH
#define AppSettingsH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <IniFiles.hpp>

#include "User.h"
#include "Logger.h"
#include "ISettings.h"


enum class Language {
	English,
	Croatian,
    Count,
	Unknown
};

class AppSettings: public ISettings {

    private:
        Language language;
        UnicodeString fontFamily;

        bool enableLogging;
        LogLevel logLevel;
        LogInterval logInterval;

        bool languageChanged = false;

        UnicodeString section = "";
        static std::vector<UnicodeString> languageStrings;

    public:
        AppSettings();
        AppSettings(User user);
       	const Language& getLanguage() const;
        void setLanguage(const Language &_language);

        const UnicodeString& getFontFamily() const;
        void setFontFamily(const UnicodeString& _fontFamily);

        bool getEnableLogging() const;
        void setEnableLogging(bool _enableLogging);

        const LogLevel &getLogLevel() const;
        void setLogLevel(LogLevel _logLevel);

        const LogInterval &getLogInterval() const;
		void setLogInterval(LogInterval _logInterval);

        bool getLanguageChanged() const;
        void setLanguageChanged(bool _languageChanged);

        static const std::vector<UnicodeString>& getLanguageStrings();

        void loadDefaults() override;
        void loadSettings() override;
        void saveSettings() override;

};


#endif
