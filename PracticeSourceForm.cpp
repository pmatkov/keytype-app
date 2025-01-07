//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PracticeSourceForm.h"
#include "FileUtils.h"
#include "UIUtils.h"
#include "ENullPointerException.h"
#include "Logger.h"

#pragma package(smart_init)
#pragma link "GeneratedTextFrame"
#pragma link "ExternalSourcesFrame"
#pragma link "CustomTextFrame"
#pragma resource "*.dfm"

TFPracticeSource *FPracticeSource;
//---------------------------------------------------------------------------

__fastcall TFPracticeSource::TFPracticeSource(TComponent* Owner) : TForm(Owner) {}

__fastcall TFPracticeSource::TFPracticeSource(TComponent* Owner, TDataModule1 *_dataModule, MainSession *_mainSession, AuthenticationService *_authService) : TForm(Owner) {

	if (_dataModule && _mainSession && _authService) {

	   dataModule = _dataModule;
       mainSession = _mainSession;
       authService = _authService;

       LOGGER(LogLevel::Debug, "Created practice sources form");
	}
    else {
        throw CustomExceptions::ENullPointerException();
    }

     FrGeneratedText = UIUtils::createFrame<TFrGeneratedText>(TSGeneratedText, dataModule);
     FrExternalSources = UIUtils::createFrame<TFrExternalSources>(TSExternalSources);
     FrCustomText = UIUtils::createFrame<TFrCustomText>(TSCustomText, dataModule, authService);

     UIUtils::setFrameVisibility<TFrGeneratedText>(FrGeneratedText, true);
     UIUtils::setFrameVisibility<TFrExternalSources>(FrExternalSources, true);
     UIUtils::setFrameVisibility<TFrCustomText>(FrCustomText, true);

     UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());

}

TFrGeneratedText* TFPracticeSource::GetFrGeneratedText() const {
	return FrGeneratedText.get();
}

TFrExternalSources* TFPracticeSource::GetFrExternalSources() const {
	return FrExternalSources.get();
}

TFrCustomText* TFPracticeSource::GetFrCustomText() const {
	return FrCustomText.get();
}
//---------------------------------------------------------------------------


