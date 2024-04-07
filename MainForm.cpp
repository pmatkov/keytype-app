//---------------------------------------------------------------------------

#include "MainForm.h"
#include "UIUtils.h"
#include "TextUtils.h"
#include "ENullPointerException.h"
#include "GameThread.h"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma link "MainFrame"
#pragma link "PracticeFrame"
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner), logger(Logger::getLogger())  {

	FrMain = UIUtils::createFrame<TFrMain>(this);
	UIUtils::setFrameVisibility<TFrMain>(FrMain, true);

	LOGGER(LogLevel::Debug, "Created main form");
}


void TFMain::setMainSession(std::unique_ptr<MainSession> _mainSession) {

    if (_mainSession) {
      	mainSession = std::move(_mainSession);

		UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());
        UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());

       	LOGGER(LogLevel::Debug, "Main session moved");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFMain::setAuthenticationService(std::unique_ptr<AuthenticationService> _authService) {

    if (_authService) {
      	authService = std::move(_authService);

       	LOGGER(LogLevel::Debug, "Main session moved");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

// dispatch char messages for processing

void __fastcall TFMain::WndProc(Messages::TMessage &Message) {

    switch (Message.Msg) {

        case WM_CHAR: {

            if (FrPractice && FrPractice->Visible) {
                FrPractice->processCharMessages(Message.WParam);
            }
            else if (FrFlyingWords && FrFlyingWords->Visible) {
            	FrFlyingWords->processCharMessages(Message.WParam);
            }
            break;
        }
        default: {
            TForm::WndProc(Message);
        }
	}
}

void __fastcall TFMain::MenuSubitemPracticeNewClick(TObject *Sender)
{

	if (!typingSession && !parser && !FrPractice) {
        typingSession = std::make_unique<TypingSession>();
        parser = std::make_unique<Parser>(mainSession.get(), typingSession.get());

		FrPractice = UIUtils::createFrame<TFrPractice>(this, parser.get(), mainSession.get(), typingSession.get());

        //  set subclass procedure for RETextBox
		SetWindowSubclass(FrPractice->RETextBox->Handle, &FrPractice->RESubclass, 0, 0);
	}

	if (FrMain && FrMain->Visible) {
		UIUtils::switchFrames<TFrMain, TFrPractice>(FrMain, FrPractice);
	}

    // terminate thread and cleanup
	else if (FrFlyingWords && FrFlyingWords->Visible) {

    	FrFlyingWords->getGameEngine().threadTerminate();
        FrFlyingWords->getGameEngine().gameCleanup();
		UIUtils::switchFrames<TFrFlyingWords, TFrPractice>(FrFlyingWords, FrPractice);
	}
}

void __fastcall TFMain::MenuSubitemPreferencesClick(TObject *Sender)
{

	if (!FPreferences) {
		FPreferences = std::make_unique<TFPreferences>(nullptr, mainSession.get(), authService.get());
		FPreferences->Position = poMainFormCenter;
	}

    if (typingSession) {
		typingSession->setSessionStatus(SessionStatus::Paused);
		FrPractice->setPracticeStatus(SessionStatus::Paused);

        FrPractice->clearCaret(mainSession->getTypingSettings().getCaretType(), typingSession->getTextSource().getCharIndex()-1);
        parser->setInputEnabled(false);
    }

    if (FPreferences->ShowModal() == mrOk) {

        if (mainSession->getAppSettings().getLanguageChanged()) {
            UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());
            mainSession->getAppSettings().setLanguageChanged(false);
        }

        if (typingSession) {
            typingSession->setSessionStatus(SessionStatus::Initialized);
            FrPractice->setPracticeStatus(SessionStatus::Initialized);
        }
    }
}

void __fastcall TFMain::MenuSubitemFlyingWordsClick(TObject *Sender)
{
	if (!FrFlyingWords) {
		FrFlyingWords = UIUtils::createFrame<TFrFlyingWords>(this);
	}

	if (FrMain && FrMain->Visible) {
		UIUtils::switchFrames<TFrMain, TFrFlyingWords>(FrMain, FrFlyingWords);
	}
	else if (FrPractice && FrPractice->Visible) {
		UIUtils::switchFrames<TFrPractice, TFrFlyingWords>(FrPractice, FrFlyingWords);
	}
}



