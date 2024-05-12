//---------------------------------------------------------------------------

#include <windows.h>
#include <memory>
#include <algorithm>

#include "MainForm.h"
#include "PracticeFrame.h"
#include "Generator.h"
#include "UIUtils.h"
#include "TextUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"


//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma link "TypingStatsFrame"
#pragma link "TypingTextFrame"
#pragma resource "*.dfm"

TFrPractice *FrPractice;
//---------------------------------------------------------------------------
__fastcall TFrPractice::TFrPractice(TComponent* Owner) : TFrame(Owner) {}

__fastcall TFrPractice::TFrPractice(TComponent* Owner, TDataModule1 *_dataModule, Parser* _parser, MainSession *_mainSession, TypingSession *_typingSession) : TFrame(Owner) {

	if (_dataModule && _parser && _mainSession && _typingSession) {

       dataModule = _dataModule;
       parser = _parser;
       mainSession = _mainSession;
	   typingSession = _typingSession;

       FrTypingStats->setMainSession(mainSession);
       FrTypingStats->setTypingSession(typingSession);

       FrTypingText->setMainSession(mainSession);
       FrTypingText->setTypingSession(typingSession);
       FrTypingText->setParser(parser);
       FrTypingText->setFrameTypingStats(FrTypingStats);

       typingSession->setSessionStatus(SessionStatus::Initialized);
       FrTypingText->setTypingStatus(Initialized);

       LOGGER(LogLevel::Debug, "Practice frame displayed");

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}



// display practice options

void __fastcall TFrPractice::FrOptionsBtOptionsClick(TObject *Sender)
{
	FPracticeOptions = std::make_unique<TFPracticeOptions>(nullptr, dataModule, mainSession);
    FPracticeOptions->Position = poMainFormCenter;

	typingSession->setSessionStatus(SessionStatus::Paused);
	FrTypingText->setTypingStatus(SessionStatus::Paused);
    parser->setInputEnabled(false);

	if (FPracticeOptions->ShowModal() == mrOk) {

    	LOGGER(LogLevel::Debug, "Practice options displayed");

		int index = FPracticeOptions->PCSourceText->ActivePageIndex;
		TTabSheet* activeTab = FPracticeOptions->PCSourceText->Pages[index];

		if (activeTab) {

			switch (index) {

				case 0: {

//					TRadioGroup* radiogroup = FPracticeOptions->GetFrGeneratedText()->RGGeneratedText;
//
//					if (radiogroup && radiogroup->ItemIndex == 0) {
//
//						UnicodeString letters = "";
//
//						std::vector<TToolButton *> buttons = FPracticeOptions->GetFrGeneratedText()->getButtons();
//
//                        for (int i = 0; i < buttons.size(); i++) {
//                            if (buttons[i] && buttons[i]->Down) {
//                                 letters += UnicodeString(buttons[i]->Caption);
//                            }
//                        }
//
//						bool uppercase = FPracticeOptions->GetFrGeneratedText()->CBCapitalLetters->Checked;
//						bool numbers = FPracticeOptions->GetFrGeneratedText()->CBNumbers->Checked;
//						bool punctuation = FPracticeOptions->GetFrGeneratedText()->CBPunctuation->Checked;
//
//						if (letters.Length() > 0 || numbers || punctuation) {
//
//							 UnicodeString newText = Generator::generateText(letters, uppercase, numbers, punctuation, 128);
//                             typingSession->setTextSource(TextSource(newText));
//
//                             typingSession->setSessionStatus(SessionStatus::Restarted);
//							 setTypingStatus(SessionStatus::Restarted);
//						}
//					}
//					else {
//
//
//					}
                }
			default:
				;
			}
		}
	}

	this->SetFocus();
}


void TFrPractice::processCharMessages(WPARAM wParam) {

 	FrTypingText->processCharMessages(wParam);

}



