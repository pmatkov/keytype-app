//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.UITypes.hpp>

#include "MainForm.h"
#include "PracticeForm.h"
#include "TCRichEdit.h"
#include "Generator.h"

#define LETTERS 26
#define SPACE_BAR 0x20

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner) {

	iocontrol = std::make_unique<IOControl>();
	session = std::make_unique<PracticeSession>();

	this->setStatusInfo(Initial);

}


void TFMain::setCharStyle(TRichEdit* richEdit, int charIndex, TFontStyle style, bool status) {

	if (charIndex >= 0 && charIndex < richEdit->Text.Length())
	{
		richEdit->SelStart = charIndex;
		richEdit->SelLength = 1;

		if (status) 
			richEdit->SelAttributes->Style = richEdit->SelAttributes->Style << style;
		else
		  richEdit->SelAttributes->Style = richEdit->SelAttributes->Style >> style;
	}
}

void TFMain::setCharColor(TRichEdit* richEdit, int charIndex, TColor textColor) {

	if (charIndex >= 0 && charIndex < richEdit->Text.Length())
	{
		richEdit->SelStart = charIndex;
		richEdit->SelLength = 1;
		richEdit->SelAttributes->Color = textColor;
	}
}

void TFMain::setTextColor(TRichEdit* richEdit, TColor textColor) {

	richEdit->SelStart = 0;
	richEdit->SelLength = richEdit->Text.Length();
	richEdit->SelAttributes->Color = textColor;
}


void TFMain::setStatusInfo(StartControl status)  {

	switch (status) {
		case Initial: {
			TextBox->Lines->Add(session->getTextsource().getText());
			TextBox->Paragraph->Alignment = taCenter;
			setTextColor(TextBox, clSilver);
			StartLabel->Caption = "Press space bar to start the practice";
			break;

		}
		case Start: {
			StartLabel->Visible = false;
			setTextColor(TextBox, clBlack);
			setCharStyle(TextBox, 0, fsUnderline, true);
			break;

		}
		case Restart: {
			TextBox->Lines->Clear();
			TextBox->Lines->Add(session->getTextsource().getText());
			StartLabel->Visible = true;
			setTextColor(TextBox, clSilver);
			StartLabel->Caption = "Press space bar to start the practice";
			break;

		}
		case Resume: {
			StartLabel->Visible = false;
			setTextColor(TextBox, clBlack);
			break;

		}
		case Pause: {
			StartLabel->Visible = true;
			setTextColor(TextBox, clSilver);
			StartLabel->Caption = "Press space bar to resume the practice";
			break;

		}

	default:
		;
	}

}



//---------------------------------------------------------------------------


void __fastcall TFMain::WndProc(Messages::TMessage &message) {


	if (message.Msg == WM_CHAR) {

		wchar_t capturedKeyStroke = iocontrol->getKeyStroke(message.WParam);

		if (capturedKeyStroke == SPACE_BAR && !iocontrol->isBufferingEnabled()) {
			if (session->isPaused()) {
				session->setPaused(false);
				this->setStatusInfo(Resume);
			}
			else
				this->setStatusInfo(Start);

			iocontrol->setBufferingEnabled(true);
		}
		else if (capturedKeyStroke && iocontrol->isBufferingEnabled()) {

			if (capturedKeyStroke == session->getTextsource().getCurrentChar()) {

				setCharStyle(TextBox, session->getTextsource().getCharIndex()-1, fsUnderline, false);

				if (session->isMistake()) {
					setCharColor(TextBox, session->getTextsource().getCharIndex()-1, clRed);
					session->setMistake(false);
				}
				else  {
					setCharColor(TextBox, session->getTextsource().getCharIndex()-1, clSilver);
				}

				session->increaseCharIndex();

				setCharStyle(TextBox, session->getTextsource().getCharIndex()-1, fsUnderline, true);
			}
			else {
				session->setMistake(true);
				setCharStyle(TextBox, session->getTextsource().getCharIndex()-1, fsUnderline, false);
				setCharColor(TextBox, session->getTextsource().getCharIndex()-1, clRed);

			}

		}
	}

	else {
		TForm::WndProc(message);
	}

}

void __fastcall TFMain::FrOptionsButtonClick(TObject *Sender)
{
	TFPractice *practiceform = new TFPractice(this);

	iocontrol->setBufferingEnabled(false);

	if (practiceform->ShowModal() == mrOk) {

		int index = practiceform->PCSourceText->ActivePageIndex;
		TTabSheet* activeTab = practiceform->PCSourceText->Pages[index];

		if (activeTab) {

			switch (index) {
				case 0: {

					TRadioGroup* radiogroup = practiceform->RGGeneratedText;

					if (radiogroup && radiogroup->ItemIndex == 0) {

						UnicodeString letters = L"";

						TGroupBox* groupbox = practiceform->GBCharacters;

//						const std::vector<std::unique_ptr<TToolButton>>& buttons = practiceform->getButtons();
						std::vector<TToolButton*> buttons = practiceform->getButtons();

						for (int i = 0; i < buttons.size(); i++) {

							TToolButton* button = buttons[i];

							if (button && button->Down) {
								 letters += UnicodeString(button->Caption);
							}
						}

						bool uppercase = practiceform->CBCapitalLetters->Checked;
						bool numbers = practiceform->CBNumbers->Checked;
						bool punctuation = practiceform->CBPunctuation->Checked;

						if (letters.Length() > 0 || numbers || punctuation) {

							 UnicodeString newText = Generator::generateText(letters, uppercase, numbers, punctuation, 128);
							 session->setTextsource(TextSource(newText));
							 this->setStatusInfo(Restart);

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
		session->setPaused(true);
		this->setStatusInfo(Pause);
    }

	delete practiceform;

	this->ActiveControl = NULL;

}
//---------------------------------------------------------------------------


