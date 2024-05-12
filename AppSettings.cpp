//---------------------------------------------------------------------------

#pragma hdrstop

#include "AppSettings.h"
#include "FileUtils.h"
#include "MainSession.h"
#include "EnumUtils.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

AppSettings::AppSettings(){}

AppSettings::AppSettings(User user) {

    if (user.getUserType() == UserType::Guest) {
       	loadDefaults();
    }
    else {
    	section = user.getUsername();
        loadSettings();
    }
}

const Language& AppSettings::getLanguage() const {
	return language;
}

void AppSettings::setLanguage(const Language &_language) {
	language = _language;
}

const UnicodeString& AppSettings::getFontFamily() const {
    return fontFamily;
}

void AppSettings::setFontFamily(const UnicodeString& _fontFamily) {
	fontFamily = _fontFamily;
}

bool AppSettings::getEnableLogging() const {
   return enableLogging;
}

void AppSettings::setEnableLogging(bool _enableLogging) {
    enableLogging = _enableLogging;
//    Logger::getLogger().setEnableLogging(enableLogging);
}

bool AppSettings::getLanguageChanged() const {
    return languageChanged;
}
void AppSettings::setLanguageChanged(bool _languageChanged) {
    languageChanged = _languageChanged;
}

const LogLevel& AppSettings::getLogLevel() const {
    return logLevel;
}

void AppSettings::setLogLevel(LogLevel _logLevel) {
    logLevel  = _logLevel;
//    Logger::getLogger().setLogLevel(logLevel);
}

const LogInterval &AppSettings::getLogInterval() const {
     return logInterval;
}

void AppSettings::setLogInterval(LogInterval _logInterval) {
    logInterval = _logInterval;
//    Logger::getLogger().setLogInterval(logInterval);
}

void AppSettings::loadDefaults() {
    language = Language::English;
    fontFamily = "Segoe UI";

    enableLogging = true;
    logLevel = LogLevel::All;
    logInterval = LogInterval::Auto;
}

void AppSettings::loadSettings() {

	std::unique_ptr<TIniFile> iniFile = std::make_unique<TIniFile>(FileUtils::createAbsolutePath("Data\\settings.ini", true));

	try {

        if (!section.IsEmpty() && iniFile->SectionExists(section)) {
            language = EnumUtils::stringToEnum<Language>(languageStrings, iniFile->ReadString(section, "Language", "English"));
            fontFamily = iniFile->ReadString(section, "FontFamily", "Segoe UI");
            enableLogging = iniFile->ReadBool(section, "EnableLogging", true);
	        logLevel = Logger::getStringAsLogLevel(iniFile->ReadString(section, "LogLevel", "All"));
            logInterval = EnumUtils::stringToEnum<LogInterval>(Logger::getLogIntervalStrings(), iniFile->ReadString(section, "LogInterval", "Auto"));
        }
        else {
            loadDefaults();
        }
    }
    catch (Exception &exception)	{
         LOGGER(LogLevel::Fatal, exception.Message);
	}

}

void AppSettings::saveSettings() {

    std::unique_ptr<TIniFile> iniFile = std::make_unique<TIniFile>(FileUtils::createAbsolutePath("Data\\settings.ini", true));

    try
	{
    	if (!section.IsEmpty()) {

            iniFile->WriteString(section, "Language", EnumUtils::enumToString<Language>(languageStrings, language));
            iniFile->WriteString(section, "FontFamily", fontFamily);
            iniFile->WriteBool(section, "EnableLogging", enableLogging);
            iniFile->WriteString(section, "LogLevel",  Logger::getLogLevelAsString(logLevel));
            iniFile->WriteString(section, "LogInterval", EnumUtils::enumToString<LogInterval>(Logger::getLogIntervalStrings(), logInterval));
        }

    }
    catch (Exception &exception)	{
         LOGGER(LogLevel::Fatal, exception.Message);
	}
}


const std::vector<UnicodeString>& AppSettings::getLanguageStrings() {
    return languageStrings;
}

std::vector<UnicodeString> AppSettings::languageStrings = {"English", "Croatian"};
