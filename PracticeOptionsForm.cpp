//---------------------------------------------------------------------------

#include "PracticeOptionsForm.h"
#include "FileUtils.h"
#include "UIUtils.h"
#include "DcWord.h"
#include "ENullPointerException.h"
#include "Logger.h"

#pragma hdrstop
#pragma package(smart_init)
#pragma link "GeneratedTextFrame"
#pragma link "ExternalSourcesFrame"
#pragma link "CustomTextFrame"
#pragma resource "*.dfm"

TFPracticeOptions *FPracticeOptions;
//---------------------------------------------------------------------------

__fastcall TFPracticeOptions::TFPracticeOptions(TComponent* Owner) : TForm(Owner) {}

__fastcall TFPracticeOptions::TFPracticeOptions(TComponent* Owner, MainSession *_mainSession) : TForm(Owner) {

	if (_mainSession) {
	   mainSession = _mainSession;
	}
    else {
        throw CustomExceptions::ENullPointerException();
    }

    FrGeneratedText = UIUtils::createFrame<TFrGeneratedText>(TSGeneratedText);
	FrExternalSources = UIUtils::createFrame<TFrExternalSources>(TSExternalSources);
    FrCustomText = UIUtils::createFrame<TFrCustomText>(TSCustomText);

    UIUtils::setFrameVisibility<TFrGeneratedText>(FrGeneratedText, true);
    UIUtils::setFrameVisibility<TFrExternalSources>(FrExternalSources, true);
    UIUtils::setFrameVisibility<TFrCustomText>(FrCustomText, true);

    UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());

    LOGGER(LogLevel::Debug, "Created practice form");

}

TFrGeneratedText* TFPracticeOptions::GetFrGeneratedText() const {
	return FrGeneratedText.get();
}

TFrExternalSources* TFPracticeOptions::GetFrExternalSources() const {
	return FrExternalSources.get();
}

TFrCustomText* TFPracticeOptions::GetFrCustomText() const {
	return FrCustomText.get();
}
//---------------------------------------------------------------------------


