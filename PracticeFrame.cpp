//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <memory>
#include <algorithm>

#include "MainForm.h"
#include "PracticeForm.h"
#include "PracticeFrame.h"
#include "Generator.h"
#include "UIUtils.h"
#include "TextUtils.h"
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

__fastcall TFrPractice::TFrPractice(TComponent* Owner, Parser* _parser, PracticeSession *_practiceSession) : TFrame(Owner) {
	if (_parser && _practiceSession) {

       parser = _parser;
       practiceSession = _practiceSession;

       maxChars = countMaxChars(RETextBox, FMain->getPracticeSession()->getTextSource().getText());
       setPracticeStatus(Initialized);

       LOGGER(LogLevel::Debug, "Practice frame created");

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

           	RETextBox->Text = FMain->getPracticeSession()->getTextSource().getText().SubString(1, maxChars);
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to start the practice";
            break;

        }
        case Started: {
            UIUtils::setTextColor(RETextBox, clBlack);
            UIUtils::setCharStyle(RETextBox, 0, fsUnderline, true);
            LStart->Visible = false;
            break;

        }
        case Restarted: {
            RETextBox->Lines->Clear();
    		RETextBox->Text = FMain->getPracticeSession()->getTextSource().getText().SubString(1, maxChars);
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to start the practice";
            LStart->Visible = true;
            break;

        }
        case Resumed: {
            UIUtils::setTextColor(RETextBox, clBlack);
            LStart->Visible = false;
            break;

        }
        case Paused: {
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space bar to resume the practice";
            LStart->Visible = true;
            break;

        }

	}

}

// display practice options

void __fastcall TFrPractice::FrOptionsBtOptionsClick(TObject *Sender)
{

	parser->setBufferingEnabled(false);

	if (FPractice->ShowModal() == mrOk) {

    	LOGGER(LogLevel::Debug, "Practice options displayed");

		int index = FPractice->PCSourceText->ActivePageIndex;
		TTabSheet* activeTab = FPractice->PCSourceText->Pages[index];

		if (activeTab) {

			switch (index) {

				case 0: {

					TRadioGroup* radiogroup = FPractice->GetFrGeneratedText()->RGGeneratedText;

					if (radiogroup && radiogroup->ItemIndex == 0) {

						UnicodeString letters = "";

						std::vector<TToolButton *> buttons = FPractice->GetFrGeneratedText()->getButtons();

						for (int i = 0; i < buttons.size(); i++) {

							if (buttons[i] && buttons[i]->Down) {
								 letters += UnicodeString(buttons[i]->Caption);
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


// determine max chars for RichEdit control

int TFrPractice::countMaxChars(TRichEdit *RETextBox, const UnicodeString &string) {

    std::unique_ptr<TBitmap> bitmap = std::make_unique<TBitmap>();
    std::unique_ptr<TCanvas> canvas = std::make_unique<TCanvas>();
    canvas->Handle = bitmap->Canvas->Handle;

    canvas->Font = RETextBox->Font;

    int textWidth = canvas->TextWidth(string);
    int textHeight = canvas->TextHeight(string);
    UnicodeString cpString = string;

    int maxChars = 0;
    bool oversized;

    for (int i = 0; i < RETextBox->ClientHeight/ textHeight; i++) {

        oversized = false;

        while ((float)(RETextBox->ClientWidth/ textWidth) < 1.0f || ((float)(RETextBox->ClientWidth/ textWidth) >= 1.0f && TextUtils::isWordBreak(string, cpString.Length()-1))) {
            oversized = true;
            cpString.Delete(cpString.Length(), 1);
            textWidth = canvas->TextWidth(cpString);
        }
        maxChars += cpString.Length();

        if (oversized) {
        	cpString = string;
            cpString.Delete(1, maxChars);
            textWidth = canvas->TextWidth(cpString);
        }
        else {
            break;
        }

    }

    return maxChars;

}

// estimate max chars for RichEdit control (for random text)

int TFrPractice::estimateMaxChars(TRichEdit *RETextBox) {

    std::unique_ptr<TBitmap> bitmap = std::make_unique<TBitmap>();
    std::unique_ptr<TCanvas> canvas = std::make_unique<TCanvas>();
    canvas->Handle = bitmap->Canvas->Handle;

    canvas->Font = RETextBox->Font;
    int chartWidth = canvas->TextWidth("o");
    int charHeight = canvas->TextHeight("o");

    int initialEstimate = (RETextBox->ClientWidth/ chartWidth) * (RETextBox->ClientHeight/ charHeight);
    int finalEstimate[3];

    for (int i = 0; i < 3; i++) {

    	UnicodeString generatedText = Generator::generateText("abcdefghijklmnopqrstuvwxyz", true, false, false, initialEstimate * 2);

        int textWidth = canvas->TextWidth(generatedText);
        int textHeight = canvas->TextHeight(generatedText);

        while ((float)(RETextBox->ClientWidth * (RETextBox->ClientHeight/ textHeight))/ textWidth > 1.0f)  {
            generatedText.Delete(generatedText.Length(), 1);
        }
        finalEstimate[i] = generatedText.Length();
    }

    std::sort(std::begin(finalEstimate), std::end(finalEstimate));

    return finalEstimate[1];

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

