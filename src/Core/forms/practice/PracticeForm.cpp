//---------------------------------------------------------------------------

#include "PracticeForm.h"
#include "FileUtils.h"
#include "UIUtils.h"
#include "ENullPointerException.h"
#include "Logger.h"

#pragma hdrstop
#pragma package(smart_init)
#pragma link "GeneratedTextFrame"
#pragma link "ExternalSourcesFrame"
#pragma link "CustomTextFrame"
#pragma resource "*.dfm"

TFPractice *FPractice;
//---------------------------------------------------------------------------

__fastcall TFPractice::TFPractice(TComponent* Owner) : TForm(Owner) {}

__fastcall TFPractice::TFPractice(TComponent* Owner, MainSession *_mainSession) : TForm(Owner) {

	if (_mainSession) {
	   mainSession = _mainSession;
	}
    else {
		throw ENullPointerException();
    }

    FrGeneratedText = UIUtils::createFrame<TFrGeneratedText>(TSGeneratedText);
	FrExternalSources = UIUtils::createFrame<TFrExternalSources>(TSExternalSources);
    FrCustomText = UIUtils::createFrame<TFrCustomText>(TSCustomText);

    UIUtils::setFrameVisibility<TFrGeneratedText>(FrGeneratedText, true);
    UIUtils::setFrameVisibility<TFrExternalSources>(FrExternalSources, true);
    UIUtils::setFrameVisibility<TFrCustomText>(FrCustomText, true);

    LOGGER(LogLevel::Debug, "Created practice form");

}

TFrGeneratedText* TFPractice::GetFrGeneratedText() const {
	return FrGeneratedText.get();
}

TFrExternalSources* TFPractice::GetFrExternalSources() const {
	return FrExternalSources.get();
}

TFrCustomText* TFPractice::GetFrCustomText() const {
	return FrCustomText.get();
}
//---------------------------------------------------------------------------


