//---------------------------------------------------------------------------

#include "PracticeForm.h"
#include "FileUtils.h"
#include "UIUtils.h"
#include "DcWord.h"

#pragma hdrstop
#pragma package(smart_init)
#pragma link "GeneratedTextFrame"
#pragma link "ExternalSourcesFrame"
#pragma link "CustomTextFrame"
#pragma resource "*.dfm"

TFPractice *FPractice;
//---------------------------------------------------------------------------
__fastcall TFPractice::TFPractice(TComponent* Owner) : TForm(Owner) {

    UIUtils::createFrame<TFrGeneratedText>(FrGeneratedText, TSGeneratedText);
    UIUtils::createFrame<TFrExternalSources>(FrExternalSources, TSExternalSources);
    UIUtils::createFrame<TFrCustomText>(FrCustomText, TSCustomText);

    UIUtils::setFrameVisibility<TFrGeneratedText>(FrGeneratedText, true);
    UIUtils::setFrameVisibility<TFrExternalSources>(FrExternalSources, true);
    UIUtils::setFrameVisibility<TFrCustomText>(FrCustomText, true);
}


void TFPractice::setSessionModule(SessionModule *_sessionModule) {

    if (_sessionModule) {
       sessionModule = _sessionModule;
    }

}

SessionModule * TFPractice::getSessionModule() {

    return sessionModule;
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


