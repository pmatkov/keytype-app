//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.UITypes.hpp>

#include "MainForm.h"
#include "PracticeForm.h"
#include "Generator.h"

#define LETTERS 26
#define SPACE 0x20

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma link "OptionsFrame"
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner) {

//	iocontrol = std::make_unique<IOControl>();
//	session = std::make_unique<PracticeSession>();

	RichEditHandle = RETextBox->Handle;
	SetWindowSubclass(RichEditHandle, &RichEditSubclass, 1, reinterpret_cast<DWORD_PTR>(this));

}


void TFMain::setSessionModule(SessionModule *_sessionModule) {

	if (_sessionModule) {
	   sessionModule = _sessionModule;
       	this->setStatusInfo(Initial);
	}

}


void TFMain::setCharStyle(TRichEdit* richEdit, int charIndex, TFontStyle style, bool status) {

	if (charIndex >= 0 && charIndex < richEdit->Text.Length()) {

		richEdit->SelStart = charIndex;
		richEdit->SelLength = 1;

		if (status) 
			richEdit->SelAttributes->Style = richEdit->SelAttributes->Style << style;
		else
		  richEdit->SelAttributes->Style = richEdit->SelAttributes->Style >> style;
	}
}

void TFMain::setCharColor(TRichEdit* richEdit, int charIndex, TColor textColor) {

	if (charIndex >= 0 && charIndex < richEdit->Text.Length()) {

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
			RETextBox->Lines->Add(sessionModule->getSession()->getTextSource().getText());
			RETextBox->Paragraph->Alignment = taCenter;
			setTextColor(RETextBox, clSilver);
			LStart->Caption = "Press space bar to start the practice";
			break;

		}
		case Start: {
			LStart->Visible = false;
			setTextColor(RETextBox, clBlack);
			setCharStyle(RETextBox, 0, fsUnderline, true);
			break;

		}
		case Restart: {
			RETextBox->Lines->Clear();
			RETextBox->Lines->Add(sessionModule->getSession()->getTextSource().getText());
			LStart->Visible = true;
			setTextColor(RETextBox, clSilver);
			LStart->Caption = "Press space bar to start the practice";
			break;

		}
		case Resume: {
			LStart->Visible = false;
			setTextColor(RETextBox, clBlack);
			break;

		}
		case Pause: {
			LStart->Visible = true;
			setTextColor(RETextBox, clSilver);
			LStart->Caption = "Press space bar to resume the practice";
			break;

		}

	}

}

//---------------------------------------------------------------------------

void __fastcall TFMain::WndProc(Messages::TMessage &message) {

	switch (message.Msg) {

		case WM_CHAR: {

			wchar_t wch = sessionModule->getIOControl()->getChar(message.WParam);

			if (wch == SPACE && !sessionModule->getIOControl()->isBufferingEnabled()) {

				if (sessionModule->getSession()->isPaused()) {

					sessionModule->getSession()->setPaused(false);
					this->setStatusInfo(Resume);
				}
				else {
					this->setStatusInfo(Start);
				}

				sessionModule->getIOControl()->setBufferingEnabled(true);
			}
			else if (wch && sessionModule->getIOControl()->isBufferingEnabled()) {

				if (wch == sessionModule->getSession()->getTextSource().getCurrentChar()) {

					setCharStyle(RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, fsUnderline, false);

					if (sessionModule->getSession()->isMistake()) {
						setCharColor(RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, clRed);
						sessionModule->getSession()->setMistake(false);
					}
					else  {
						setCharColor(RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, clSilver);
					}

					sessionModule->getSession()->increaseCharIndex();

					setCharStyle(RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, fsUnderline, true);
				}
				else {
					sessionModule->getSession()->setMistake(true);
					setCharStyle(RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, fsUnderline, false);
					setCharColor(RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, clRed);

				}

			}
		}
		break;

		default: {
			TForm::WndProc(message);
		}
	}

}


void __fastcall TFMain::BtOptionsButtonClick(TObject *Sender)
{
//	TFPractice *practiceform = new TFPractice(this);

	sessionModule->getIOControl()->setBufferingEnabled(false);

	if (FPractice->ShowModal() == mrOk) {

		int index = FPractice->PCSourceText->ActivePageIndex;
		TTabSheet* activeTab = FPractice->PCSourceText->Pages[index];

		if (activeTab) {

			switch (index) {

				case 0: {

					TRadioGroup* radiogroup = FPractice->RGGeneratedText;

					if (radiogroup && radiogroup->ItemIndex == 0) {

						UnicodeString letters = L"";

						std::vector<TToolButton*> buttons = FPractice->getButtons();

						for (int i = 0; i < buttons.size(); i++) {

							TToolButton* button = buttons[i];

							if (button && button->Down) {
								 letters += UnicodeString(button->Caption);
							}
						}

						bool uppercase = FPractice->CBCapitalLetters->Checked;
						bool numbers = FPractice->CBNumbers->Checked;
						bool punctuation = FPractice->CBPunctuation->Checked;

						if (letters.Length() > 0 || numbers || punctuation) {

							 UnicodeString newText = Generator::generateText(letters, uppercase, numbers, punctuation, 128);
							 sessionModule->getSession()->setTextSource(TextSource(newText));
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
		sessionModule->getSession()->setPaused(true);
		this->setStatusInfo(Pause);
    }

//	delete practiceform;

	this->ActiveControl = nullptr;

}
//---------------------------------------------------------------------------

LRESULT CALLBACK TFMain::RichEditSubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{

	switch (msg) {

		case WM_SETFOCUS:
			HideCaret(hwnd);
			break;

		case WM_KILLFOCUS:
			ShowCaret(hwnd);
			break;

		case WM_SETCURSOR:
			Screen->Cursor = crArrow;
			return TRUE;

		case WM_CHAR:
			PostMessage(GetParent(hwnd), WM_CHAR, wParam, lParam);
			break;

		default:
            return DefSubclassProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}
