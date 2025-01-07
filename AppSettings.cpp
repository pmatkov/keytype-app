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
    	username = user.getUsername();
        loadSettings();
    }
    LOGGER(LogLevel::Debug, "Created app settings");
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
}

const ArchiveLogLimit &AppSettings::getArchiveLogLimit() const {
     return archiveLogLimit;
}

void AppSettings::setArchiveLogLimit(ArchiveLogLimit _archiveLogLimit) {
    archiveLogLimit = _archiveLogLimit;
}

void AppSettings::loadDefaults() {
    language = Language::English;
    fontFamily = "Segoe UI";

    enableLogging = true;
    logLevel = LogLevel::All;
    archiveLogLimit = ArchiveLogLimit::Auto;
}

void AppSettings::loadSettings() {

	std::unique_ptr<TIniFile> iniFile = std::make_unique<TIniFile>(FileUtils::createAbsolutePath("Data\\settings.ini", true));

	try {

        if (!username.IsEmpty() && iniFile->SectionExists(username)) {

            language = EnumUtils::stringToEnum<Language>(languageStrings, iniFile->ReadString(username, "Language", "English"));
            fontFamily = iniFile->ReadString(username, "FontFamily", "Segoe UI");
            enableLogging = iniFile->ReadBool(username, "EnableLogging", true);
            logLevel = Logger::getStringAsLogLevel(iniFile->ReadString(username, "LogLevel", "All"));
            archiveLogLimit = EnumUtils::stringToEnum<ArchiveLogLimit>(Logger::getArchiveLogLimitStrings(), iniFile->ReadString(username, "ArchiveLogLimit", "Auto"));
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
    	if (!username.IsEmpty()) {

            iniFile->WriteString(username, "Language", EnumUtils::enumToString<Language>(languageStrings, language));
            iniFile->WriteString(username, "FontFamily", fontFamily);
            iniFile->WriteBool(username, "EnableLogging", enableLogging);
            iniFile->WriteString(username, "LogLevel",  Logger::getLogLevelAsString(logLevel));
            iniFile->WriteString(username, "ArchiveLogLimit", EnumUtils::enumToString<ArchiveLogLimit>(Logger::getArchiveLogLimitStrings(), archiveLogLimit));
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
