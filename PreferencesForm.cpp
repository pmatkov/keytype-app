//---------------------------------------------------------------------------

#include <vcl.h>

#include "PreferencesForm.h"
#include "ENullPointerException.h"
#include "AppSettings.h"
#include "Logger.h"
#include "UIUtils.h"
#include "EnumUtils.h"
#include "UIUtils.h"
#include "reinit.hpp"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

TFPreferences *FPreferences;
//---------------------------------------------------------------------------
__fastcall TFPreferences::TFPreferences(TComponent* Owner)	: TForm(Owner)  {}

__fastcall TFPreferences::TFPreferences(TComponent* Owner, MainSession *_mainSession, AuthenticationService *_authService)  : TForm(Owner)
{
    if (_mainSession) {

    	mainSession = _mainSession;
        authService = _authService;

        UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());

        setAppSettingsItems();
        setTypingSettingsItems();

       	LOGGER(LogLevel::Debug, "Preferences displayed");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}


void TFPreferences::setAppSettingsItems() {

   UIUtils::setComboBoxItems(CBLanguage, AppSettings::getLanguageStrings(), EnumUtils::enumToString<Language>(AppSettings::getLanguageStrings(), mainSession->getAppSettings().getLanguage()));

   if (CBFont1->Items->Count == 0) {
   	UIUtils::setComboBoxItems(CBFont1, UIUtils::getScreenFonts(), mainSession->getAppSettings().getFontFamily());
   }
   else {
   	CBFont1->ItemIndex = UIUtils::findItemIndex(UIUtils::getScreenFonts(), mainSession->getAppSettings().getFontFamily());
   }

   CBLoggingEnable->Checked = mainSession->getAppSettings().getEnableLogging();

   if  (CBLoggingEnable->Checked) {
        UIUtils::setComboBoxItems(CBLogging, Logger::getLogLevelStrings(), Logger::getLogLevelAsString(mainSession->getAppSettings().getLogLevel()));
        UIUtils::setComboBoxItems(CBLogInterval, Logger::getLogIntervalStrings(), EnumUtils::enumToString<LogInterval>(Logger::getLogIntervalStrings(), mainSession->getAppSettings().getLogInterval()));
   }
   else {
       CBLogging->Enabled = false;
       CBLogInterval->Enabled = false;
   }
}

void TFPreferences::setTypingSettingsItems() {
   UIUtils::setComboBoxItems(CBCaret, TypingSettings::getCaretTypeStrings(), EnumUtils::enumToString<CaretType>(TypingSettings::getCaretTypeStrings(), mainSession->getTypingSettings().getCaretType()));
   UIUtils::setComboBoxItems(CBSeparator, TypingSettings::getSeparatorTypeStrings(), EnumUtils::enumToString<SeparatorType>(TypingSettings::getSeparatorTypeStrings(), mainSession->getTypingSettings().getSeparatorType()));

   if (CBFont2->Items->Count == 0) {
   	UIUtils::setComboBoxItems(CBFont2, UIUtils::getScreenFonts(), mainSession->getTypingSettings().getFontFamily());
   }
   else {
   	CBFont2->ItemIndex = UIUtils::findItemIndex(UIUtils::getScreenFonts(), mainSession->getTypingSettings().getFontFamily());
   }
   UIUtils::setComboBoxItems(CBFontSize, {"9", "10", "11", "12"}, IntToStr(mainSession->getTypingSettings().getFontSize()));

   CBMistake->Checked = mainSession->getTypingSettings().getStopOnMistake();
   CBConsecutiveMistakes->Checked = mainSession->getTypingSettings().getCountConsecutiveMistakes();
   CBSpeed->Checked = mainSession->getTypingSettings().getDisplaySpeed();
   CBAccuracy->Checked = mainSession->getTypingSettings().getDisplayAccuracy();

}

void __fastcall TFPreferences::BtReset1Click(TObject *Sender)
{
    mainSession->getAppSettings().loadDefaults();
    setAppSettingsItems();
}

void __fastcall TFPreferences::BtReset2Click(TObject *Sender)
{
      mainSession->getTypingSettings().loadDefaults();
      setTypingSettingsItems();
}

void __fastcall TFPreferences::BtAcceptClick(TObject *Sender)
{
    if (authService->getUser().getUserType() == UserType::Registered) {

    	mainSession->getAppSettings().saveSettings();
        mainSession->getTypingSettings().saveSettings();

        LOGGER(LogLevel::Debug, "Preferences saved");
    }
}

void __fastcall TFPreferences::CBLanguageChange(TObject *Sender)
{

	int selectedIndex = CBLanguage->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBLanguage->Items->Strings[selectedIndex];
        mainSession->getAppSettings().setLanguage(EnumUtils::stringToEnum<Language>(mainSession->getAppSettings().getLanguageStrings(), selectedText));
        mainSession->getAppSettings().setLanguageChanged(true);
    }

}
void __fastcall TFPreferences::CBMistakeClick(TObject *Sender)
{
  	mainSession->getTypingSettings().setStopOnMistake(CBMistake->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBConsecutiveMistakesClick(TObject *Sender)
{
     mainSession->getTypingSettings().setCountConsecutiveMistakes(CBConsecutiveMistakes->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBSpeedClick(TObject *Sender)
{
	mainSession->getTypingSettings().setDisplaySpeed(CBSpeed->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBAccuracyClick(TObject *Sender)
{
   	mainSession->getTypingSettings().setDisplayAccuracy(CBAccuracy->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBCaretChange(TObject *Sender)
{
	int selectedIndex = CBCaret->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBCaret->Items->Strings[selectedIndex];
        mainSession->getTypingSettings().setCaretType(EnumUtils::stringToEnum<CaretType>(mainSession->getTypingSettings().getCaretTypeStrings(), selectedText));
    }
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBSeparatorChange(TObject *Sender)
{
   	int selectedIndex = CBSeparator->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBSeparator->Items->Strings[selectedIndex];
        mainSession->getTypingSettings().setSeparatorType(EnumUtils::stringToEnum<SeparatorType>(mainSession->getTypingSettings().getSeparatorTypeStrings(), selectedText));

    }
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBFont2Change(TObject *Sender)
{
	int selectedIndex = CBFont2->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBFont2->Items->Strings[selectedIndex];
        mainSession->getTypingSettings().setFontFamily(selectedText);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBFontSizeChange(TObject *Sender)
{
	int selectedIndex = CBFontSize->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBFontSize->Items->Strings[selectedIndex];
        mainSession->getTypingSettings().setFontSize(StrToInt(selectedText));
    }
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBLoggingEnableClick(TObject *Sender)
{
	mainSession->getAppSettings().setEnableLogging(CBLoggingEnable->Checked);

    if  (!CBLoggingEnable->Checked) {
    	CBLogging->Enabled = false;
       	CBLogInterval->Enabled = false;
    }
    else {
    	CBLogging->Enabled = true;
       	CBLogInterval->Enabled = true;
    }
}

void __fastcall TFPreferences::CBLoggingChange(TObject *Sender)
{
	int selectedIndex = CBLogging->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBLogging->Items->Strings[selectedIndex];
        mainSession->getAppSettings().setLogLevel(Logger::getStringAsLogLevel(selectedText));
    }
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBFont1Change(TObject *Sender)
{
	int selectedIndex = CBFont1->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBFont1->Items->Strings[selectedIndex];
        mainSession->getTypingSettings().setFontFamily(selectedText);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFPreferences::CBLogIntervalChange(TObject *Sender)
{
	int selectedIndex = CBLogInterval->ItemIndex;

    if (selectedIndex != -1) {
    	UnicodeString selectedText = CBLogInterval->Items->Strings[selectedIndex];
        mainSession->getAppSettings().setLogInterval(EnumUtils::stringToEnum<LogInterval>(Logger::getLogIntervalStrings(), selectedText));
    }
}

