//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MForm.h"
#include "TCRichEdit.h"
#include <System.UITypes.hpp>

#define SPACE_BAR 0x20

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner) {

	iocontrol = new IOControl();
	session = new PracticeSession();
	controller = new PracticeController(this, iocontrol, session);

	TextBox->Paragraph->Alignment = taCenter;
	TextBox->Lines->Add(session->getTextsource().getText());
	SetTextColor(TextBox, clSilver);

	// delete objects


}

void __fastcall TFMain::WndProc(Messages::TMessage &message) {

	if (message.Msg == WM_CHAR)
		controller->processKeyStroke(message.WParam);
	else
		TForm::WndProc(message);
}


void TFMain::SetCharUnderline(TRichEdit* richEdit, int charIndex) {

	if (charIndex >= 0 && charIndex < richEdit->Text.Length())
	{
		richEdit->SelStart = charIndex;
		richEdit->SelLength = 1;
		richEdit->SelAttributes->Style = richEdit->SelAttributes->Style << fsUnderline;
	}
}

void TFMain::RemoveCharUnderline(TRichEdit* richEdit, int charIndex) {

	if (charIndex >= 0 && charIndex < richEdit->Text.Length())
	{
		richEdit->SelStart = charIndex;
		richEdit->SelLength = 1;
		richEdit->SelAttributes->Style = richEdit->SelAttributes->Style >> fsUnderline;

	}
}

void TFMain::SetCharColor(TRichEdit* richEdit, int charIndex, TColor textColor) {

	if (charIndex >= 0 && charIndex < richEdit->Text.Length())
	{
		richEdit->SelStart = charIndex;
		richEdit->SelLength = 1;
		richEdit->SelAttributes->Color = textColor;

	}
}

void TFMain::SetTextColor(TRichEdit* richEdit, TColor textColor) {

	richEdit->SelStart = 0;
	richEdit->SelLength = richEdit->Text.Length();
	richEdit->SelAttributes->Color = textColor;

}


//void __fastcall TFMain::StartLabelClick(TObject *Sender)
//{
//
//	  controller->startPractice();
//}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

