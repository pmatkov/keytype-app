//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#include "MainForm.h"
#include "PracticeForm.h"
#include "PracticeFrame.h"
#include "Generator.h"
#include "UIUtils.h"
#include "ENullPointerException.h"
#include "Logger.h"

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma resource "*.dfm"
TFrPractice *FrPractice;
//---------------------------------------------------------------------------
__fastcall TFrPractice::TFrPractice(TComponent* Owner) : TFrame(Owner) {}

__fastcall TFrPractice::TFrPractice(TComponent* Owner, Parser* _parser, PracticeSession *_practiceSession)
	: TFrame(Owner)
{
	if (_parser && _practiceSession) {
	   parser = _parser;
       practiceSession = _practiceSession;

       setPracticeStatus(Initialized);

       LOGGER(LogLevel::Debug, "Assign parser and practice session");
	}
    else {
        throw ENullPointerException();
    }
}

void TFrPractice::setPracticeForm(TFPractice *_FPractice) {
	FPractice = _FPractice;
}

// change frame appearance based on practice status

void TFrPractice::setPracticeStatus(PracticeStatus status)  {

	switch (status) {

        LOGGER(LogLevel::Debug, "Change practice status");

        case Initialized: {
            RETextBox->Lines->Add(FMain->getPracticeSession()->getTextSource().getText());
            RETextBox->Paragraph->Alignment = taCenter;
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to start the practice";
            break;

        }
        case Started: {
            LStart->Visible = false;
            UIUtils::setTextColor(RETextBox, clBlack);
            UIUtils::setCharStyle(RETextBox, 0, fsUnderline, true);
            break;

        }
        case Restarted: {
            RETextBox->Lines->Clear();
            RETextBox->Lines->Add(FMain->getPracticeSession()->getTextSource().getText());
            LStart->Visible = true;
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to start the practice";
            break;

        }
        case Resumed: {
            LStart->Visible = false;
            UIUtils::setTextColor(RETextBox, clBlack);
            break;

        }
        case Paused: {
            LStart->Visible = true;
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to resume the practice";
            break;

        }

	}

}

// change practice options

void __fastcall TFrPractice::FrOptionsBtOptionsClick(TObject *Sender)
{

	parser->setBufferingEnabled(false);

	if (FPractice->ShowModal() == mrOk) {

    LOGGER(LogLevel::Debug, "Options form");

		int index = FPractice->PCSourceText->ActivePageIndex;
		TTabSheet* activeTab = FPractice->PCSourceText->Pages[index];

		if (activeTab) {

			switch (index) {

				case 0: {

					TRadioGroup* radiogroup = FPractice->GetFrGeneratedText()->RGGeneratedText;

					if (radiogroup && radiogroup->ItemIndex == 0) {

						UnicodeString letters = "";

						std::vector<TToolButton*> buttons = FPractice->GetFrGeneratedText()->getButtons();

						for (int i = 0; i < buttons.size(); i++) {

							TToolButton* button = buttons[i];

							if (button && button->Down) {
								 letters += UnicodeString(button->Caption);
							}
						}

						bool uppercase = FPractice->GetFrGeneratedText()->CBCapitalLetters->Checked;
						bool numbers = FPractice->GetFrGeneratedText()->CBNumbers->Checked;
						bool punctuation = FPractice->GetFrGeneratedText()->CBPunctuation->Checked;

						if (letters.Length() > 0 || numbers || punctuation) {

							 UnicodeString newText = Generator::generateText(letters, uppercase, numbers, punctuation, 128);
                             practiceSession->setTextSource(TextSource(newText));
							 setPracticeStatus(Restarted);
						}
					}
					else {


					}
                }
			default:
				;
			}
		}
	}
	else {
		practiceSession->setPaused(true);
		setPracticeStatus(Paused);
	}

	this->SetFocus();
}

// forward all char messages to main form
void __fastcall TFrPractice::WndProc(TMessage &Message)
{
	switch (Message.Msg) {
        case WM_CHAR:
//        	SendMessage(FMain->Handle, WM_CHAR, Message.WParam, 0);
			PostMessage(FMain->Handle, WM_CHAR, Message.WParam, 0);
            break;

        default:
            TFrame::WndProc(Message);
    }
}
