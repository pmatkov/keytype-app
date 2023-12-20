//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#include "MainForm.h"
#include "PracticeForm.h"
#include "PracticeFrame.h"
#include "Generator.h"
#include "UIUtils.h"

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma resource "*.dfm"
TFrPractice *FrPractice;
//---------------------------------------------------------------------------
__fastcall TFrPractice::TFrPractice(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------

void TFrPractice::setStatusInfo(StartControl status)  {

	switch (status) {

        case Initial: {
            RETextBox->Lines->Add(FMain->getSessionModule()->getSession()->getTextSource().getText());
            RETextBox->Paragraph->Alignment = taCenter;
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space to start the practice";
            break;

        }
        case Start: {
            LStart->Visible = false;
            UIUtils::setTextColor(RETextBox, clBlack);
            UIUtils::setCharStyle(RETextBox, 0, fsUnderline, true);
            break;

        }
        case Restart: {
            RETextBox->Lines->Clear();
            RETextBox->Lines->Add(FMain->getSessionModule()->getSession()->getTextSource().getText());
            LStart->Visible = true;
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press space to start the practice";
            break;

        }
        case Resume: {
            LStart->Visible = false;
            UIUtils::setTextColor(RETextBox, clBlack);
            break;

        }
        case Pause: {
            LStart->Visible = true;
            UIUtils::setTextColor(RETextBox, clSilver);
            LStart->Caption = "Press any key to resume the practice";
            break;

        }

	}

}

void __fastcall TFrPractice::FrOptionsBtOptionsClick(TObject *Sender)
{

	FMain->getSessionModule()->getIOControl()->setBufferingEnabled(false);

	if (FPractice->ShowModal() == mrOk) {

		int index = FPractice->PCSourceText->ActivePageIndex;
		TTabSheet* activeTab = FPractice->PCSourceText->Pages[index];

		if (activeTab) {

			switch (index) {

				case 0: {

					TRadioGroup* radiogroup = FPractice->GetFrGeneratedText()->RGGeneratedText;

					if (radiogroup && radiogroup->ItemIndex == 0) {

						UnicodeString letters = L"";

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
							 FMain->getSessionModule()->getSession()->setTextSource(TextSource(newText));
							 setStatusInfo(Restart);

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
		FMain->getSessionModule()->getSession()->setPaused(true);
		setStatusInfo(Pause);
	}

	this->SetFocus();
}

void __fastcall TFrPractice::WndProc(TMessage &Message)
{
	switch (Message.Msg)
    {
        case WM_CHAR:
        	SendMessage(FMain->Handle, WM_CHAR, Message.WParam, 0);
            break;

        default:
            TFrame::WndProc(Message);
    }
}


//---------------------------------------------------------------------------

