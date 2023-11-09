//---------------------------------------------------------------------------

#include <vcl.h>
#include "PracticeForm.h"

//---------------------------------------------------------------------------

#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

TFPractice *FPractice;
//---------------------------------------------------------------------------
__fastcall TFPractice::TFPractice(TComponent* Owner) : TForm(Owner) {

	LettersToolbar->ShowCaptions = true;

	const int LETTERS = 26;

	for (int i = 0; i < LETTERS; i++) {

//		buttons.push_back(std::make_unique<TToolButton>(LettersToolbar));

		buttons.push_back(new TToolButton(LettersToolbar));
		buttons[i]->Parent = LettersToolbar;
		buttons[i]->Caption = Char('Z' - i);
		buttons[i]->Style = tbsCheck;
		buttons[i]->Width =  LettersToolbar->ButtonWidth / LETTERS/ 2;

		if (i == LETTERS/ 2) {
			buttons[i]->Wrap = true;
		}
	}

	RGGeneratedText->ItemIndex = 0;
	updateGroupBoxState();
}
//---------------------------------------------------------------------------

//const std::vector<std::unique_ptr<TToolButton>>& TFPractice::getButtons() const {
//	return buttons;
//}


const std::vector<TToolButton*>& TFPractice::getButtons() const {
	return buttons;
}


void __fastcall TFPractice::CButtonClick(TObject *Sender)
{
	  ModalResult = mrCancel;
}

void __fastcall TFPractice::updateGroupBoxState()
{
	if (RGGeneratedText->ItemIndex == 0) {

		GBCharacters->Enabled = true;
		GBWords->Enabled = false;

		changeChildControlsStatus(GBCharacters, true);
		changeChildControlsStatus(GBWords, false);

	} else {
		GBWords->Enabled = true;
		GBCharacters->Enabled = false;

		changeChildControlsStatus(GBWords, true);
		changeChildControlsStatus(GBCharacters, false);
	}
}

void TFPractice::changeChildControlsStatus(TWinControl* parentControl, Boolean status)
{
	for (int i = 0; i < parentControl->ControlCount; i++)
	{
        TControl* childControl = parentControl->Controls[i];
		childControl->Enabled = status;
	}
}

void __fastcall TFPractice::RGGeneratedTextClick(TObject *Sender)
{
	updateGroupBoxState();
}
//---------------------------------------------------------------------------

void __fastcall TFPractice::CBSelectAllClick(TObject *Sender)
{
		for (TToolButton *button : buttons) {
		button->Down = CBSelectAll->Checked ? !button->Down : false;

	}
}
//---------------------------------------------------------------------------

