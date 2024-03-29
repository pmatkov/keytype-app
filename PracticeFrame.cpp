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

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma resource "*.dfm"
TFrPractice *FrPractice;
//---------------------------------------------------------------------------
__fastcall TFrPractice::TFrPractice(TComponent* Owner) : TFrame(Owner) {}

__fastcall TFrPractice::TFrPractice(TComponent* Owner, Parser* _parser, MainSession *_mainSession, TypingSession *_typingSession) : TFrame(Owner) {
	if (_parser && _mainSession && _typingSession) {

       parser = _parser;
       mainSession = _mainSession;
       typingSession = _typingSession;

       maxChars = TextUtils::countCharsUntilWordBreak(typingSession->getTextSource().getText(), UIUtils::estimateMaxChars(RETextBox));
       setPracticeStatus(Initialized);
       typingSession->setSessionStatus(SessionStatus::Initialized);

       LOGGER(LogLevel::Debug, "Practice frame created");

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}


// change frame appearance based on practice status

void TFrPractice::setPracticeStatus(SessionStatus status)  {

	switch (status) {

        case Initialized: {

            hideStatsItems();

            // fix font change at runtime
            RETextBox->Font->Name = mainSession->getTypingSettings().getFontFamily();
            RETextBox->Font->Size = mainSession->getTypingSettings().getFontSize();

//            ShowMessage(StrToInt( RETextBox->Font->Size));

            if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Space) {
            	RETextBox->Text = typingSession->getTextSource().getText().SubString(1, maxChars);
            }
            else if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Dot) {
            	RETextBox->Text = TextUtils::replaceChar(typingSession->getTextSource().getText().SubString(1, maxChars), ' ', L'\u25E6');
            }

            UIUtils::setTextColor(RETextBox, clSilver);

            LStart->Caption = "Press space bar to start the practice";
            break;
        }
        case Started: {
            UIUtils::setTextColor(RETextBox, clBlack);

            if (mainSession->getTypingSettings().getCaretType() == CaretType::Block) {
            	UIUtils::setCharBgColor(RETextBox, 0, clSilver);
            }
            else if (mainSession->getTypingSettings().getCaretType() == CaretType::Underline) {
            	UIUtils::setCharStyle(RETextBox, 0, fsUnderline, true);
            }

            // activate the timer
            typingSession->setSessionStart();
            Timer1->Enabled = true;

            displayStatsItems();

            LStart->Visible = false;
            break;
        }
        case Restarted: {
			RETextBox->Text = typingSession->getTextSource().getText().SubString(1, maxChars);
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to start the practice";
            LStart->Visible = true;
            break;

        }
        case Resumed: {
        	UIUtils::setTextColor(RETextBox, clBlack);
            int index = typingSession->getTextSource().getCharIndex()-1;
            UIUtils::setCharColor(RETextBox, parser->getBuffer(), index, index + parser->getInsertedChars().Length(), clRed);
            LStart->Visible = false;
            break;

        }
        case Paused: {
          	hideStatsItems();
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to resume the practice";
            LStart->Visible = true;
            break;
        }
        default:
        ;

        LOGGER(LogLevel::Debug, "Practice status set");
	}

}

// display practice options

void __fastcall TFrPractice::FrOptionsBtOptionsClick(TObject *Sender)
{
    FPracticeOptions = std::make_unique<TFPracticeOptions>(nullptr, mainSession);
    FPracticeOptions->Position = poMainFormCenter;

	typingSession->setSessionStatus(SessionStatus::Paused);
    setPracticeStatus(SessionStatus::Paused);
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
//							 setPracticeStatus(SessionStatus::Restarted);
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

void TFrPractice::displayStatsItems() {

	LTime->Visible = true;
    LDisplayTime->Visible = true;
    LTime->Font->Color = clGray;
	LDisplayTime->Font->Color = clSilver;

    if (mainSession->getTypingSettings().getDisplaySpeed()) {
        LSpeed->Visible = true;
        LDisplaySpeed->Visible = true;
        LSpeed->Font->Color = clGray;
        LDisplaySpeed->Font->Color = clSilver;
    }

    if (mainSession->getTypingSettings().getDisplayAccuracy()) {
        LAccuracy->Visible = true;
        LDisplayAccuracy->Visible = true;
        LAccuracy->Font->Color = clGray;
        LDisplayAccuracy->Font->Color = clSilver;
    }

}

void TFrPractice::hideStatsItems() {
	LTime->Visible = false;
    LDisplayTime->Visible = false;

    LSpeed->Visible = false;
    LDisplaySpeed->Visible = false;

    LAccuracy->Visible = false;
    LDisplayAccuracy->Visible = false;
}

// forward all char messages to main form
void __fastcall TFrPractice::WndProc(TMessage &Message)
{
	switch (Message.Msg) {
        case WM_CHAR:
			PostMessage(FMain->Handle, WM_CHAR, Message.WParam, 0);
            break;

        default:
            TFrame::WndProc(Message);
    }
}

void __fastcall TFrPractice::Timer1Timer(TObject *Sender)
{
        if (typingSession->getSessionStatus() == SessionStatus::Started) {

        	int min = typingSession->getElapsedTime()/ 60;
        	int sec = typingSession->getElapsedTime()% 60;
            TDateTime elapsedTime = System::Sysutils::EncodeTime(0, min, sec, 0);
            LDisplayTime->Caption = FormatDateTime("hh:nn:ss", elapsedTime);

            if (mainSession->getTypingSettings().getDisplaySpeed()) {
               LDisplaySpeed->Caption = FormatFloat("0.00", typingSession->getSpeed()) + " WPM";
            }
            if (mainSession->getTypingSettings().getDisplayAccuracy()) {
               LDisplayAccuracy->Caption = FormatFloat("0.00", typingSession->getAccuracy()) + " %";
            }
    	}
}
//---------------------------------------------------------------------------

