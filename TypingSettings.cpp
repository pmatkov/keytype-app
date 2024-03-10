//---------------------------------------------------------------------------

#pragma hdrstop

#include "TypingSettings.h"
#include "registry.hpp"
#include "Logger.h"
#include "EnumUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TypingSettings::TypingSettings(){}

TypingSettings::TypingSettings(User user) {

    if (user.getUserType() == UserType::Guest) {
       	loadDefaults();
    }
    else {
        section = user.getUsername() + "\\";
        loadSettings();
    }
}

const CaretType& TypingSettings::getCaretType() const {
	return caretType;
}

void TypingSettings::setCaretType(const CaretType &_caretType) {
	caretType = _caretType;
}

const SeparatorType& TypingSettings::getSeparatorType() const {
	return separatorType;
}

void TypingSettings::setSeparatorType(const SeparatorType &_separatorType) {
	separatorType = _separatorType;
}

const UnicodeString& TypingSettings::getFontFamily() const {
    return fontFamily;
}

void TypingSettings::setFontFamily(const UnicodeString& _fontFamily) {
	fontFamily = _fontFamily;
 }

int TypingSettings::getFontSize() const {
    return fontSize;
}

void TypingSettings::setFontSize(int _fontSize) {
    fontSize = _fontSize;
}

bool TypingSettings::getStopOnMistake() const {
    return stopOnMistake;
}

void TypingSettings::setStopOnMistake(bool _stopOnMistake) {
    stopOnMistake = _stopOnMistake;
}

bool TypingSettings::getCountConsecutiveMistakes() const {
    return countConsecutiveMistakes;
}

void TypingSettings::setCountConsecutiveMistakes(bool _countConsecutiveMistakes) {
    countConsecutiveMistakes = _countConsecutiveMistakes;
}

bool TypingSettings::getDisplaySpeed() const {
    return displaySpeed;
}

void TypingSettings::setDisplaySpeed(bool _displaySpeed) {
    displaySpeed = _displaySpeed;
}

bool TypingSettings::getDisplayAccuracy() const {
    return displayAccuracy;
}

void TypingSettings::setDisplayAccuracy(bool _displayAccuracy) {
    displayAccuracy = _displayAccuracy;
}

void TypingSettings::loadDefaults() {
    caretType = CaretType::Block;
    separatorType = SeparatorType::Dot;
    fontFamily = "Segoe UI";
    fontSize = 9;

    stopOnMistake = true;
    countConsecutiveMistakes = false;
    displaySpeed = true;
    displayAccuracy = true;
}

void TypingSettings::loadSettings() {

	std::unique_ptr<TRegistry> registry = std::make_unique<TRegistry>();
  	registry->RootKey = HKEY_CURRENT_USER;

    try
	{

        if (!section.IsEmpty() && registry->OpenKeyReadOnly("Software\\KeyType\\" + section)) {


			caretType = registry->ValueExists("CaretType") ? EnumUtils::stringToEnum<CaretType>(caretTypeStrings, registry->ReadString("CaretType")) : CaretType::Underline;
			separatorType = registry->ValueExists("SeparatorType") ? EnumUtils::stringToEnum<SeparatorType>(separatorTypeStrings, registry->ReadString("SeparatorType")) : SeparatorType::Dot;
            fontFamily = registry->ValueExists("FontFamily") ? registry->ReadString("FontFamily") : "Segoe UI";
            fontSize = registry->ValueExists("FontSize") ? registry->ReadInteger("FontSize") : 9;

            stopOnMistake = registry->ValueExists("stopOnMistake") ? registry->ReadBool("stopOnMistake") : true;
            countConsecutiveMistakes = registry->ValueExists("countConsecutiveMistakes") ? registry->ReadBool("countConsecutiveMistakes") : false;
            displaySpeed = registry->ValueExists("displaySpeed") ? registry->ReadBool("displaySpeed") : true;
            displayAccuracy = registry->ValueExists("displayAccuracy") ? registry->ReadBool("displayAccuracy") : true;

            registry->CloseKey();
        }
        else {
          loadDefaults();
        }
    } catch (Exception &exception)	{
         LOGGER(LogLevel::Fatal, exception.Message);
	}

}

void TypingSettings::saveSettings() {

	std::unique_ptr<TRegistry> registry = std::make_unique<TRegistry>();
  	registry->RootKey = HKEY_CURRENT_USER;

    try
	{
        if (registry->OpenKey("Software\\KeyType\\" + section, true)) {

			registry->WriteString("CaretType", EnumUtils::enumToString<CaretType>(caretTypeStrings, caretType));
			registry->WriteString("SeparatorType", EnumUtils::enumToString<SeparatorType>(separatorTypeStrings, separatorType));
            registry->WriteString("FontFamily", fontFamily);
            registry->WriteInteger("FontSize", fontSize);

            registry->WriteBool("StopOnMistake", stopOnMistake);
            registry->WriteBool("CountConsecutiveMistakes", countConsecutiveMistakes);
            registry->WriteBool("DisplaySpeed", displaySpeed);
            registry->WriteBool("DisplayAccuracy", displayAccuracy);

            registry->CloseKey();
        }
    } catch (Exception &exception)	{
         LOGGER(LogLevel::Fatal, exception.Message);
	}

}

const std::vector<UnicodeString>& TypingSettings::getCaretTypeStrings() {
    return caretTypeStrings;
}
const std::vector<UnicodeString>& TypingSettings::getSeparatorTypeStrings() {
    return separatorTypeStrings;
}

std::vector<UnicodeString> TypingSettings::caretTypeStrings = {"Block", "Underline"};
std::vector<UnicodeString> TypingSettings::separatorTypeStrings = {"Dot", "Space"};

