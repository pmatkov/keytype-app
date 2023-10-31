//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MForm.h"
#include "TCRichEdit.h"
#include <System.UITypes.hpp>

#define SPACE_BAR 0x20

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner) {

	 controller = new PracticeController(this);

	// delete objects
//	iocontrol = new IOControl();
//	*textsource = new TextSource();
//
//	TextBox->Lines->Add(textsource->getText());
//
//	TextBox->SelStart = 0;
//	TextBox->SelLength = 1;
//	TextBox->SelAttributes->Color = clRed;


//	TRichLabel* richLabel = new TRichLabel(this);
//	richLabel->Parent = this;
//	richLabel->Left = 10;
//	richLabel->Top = 10;
//	richLabel->Width = 300;
//	richLabel->Height = 50;
//	richLabel->Caption = L"This is a rich label!";
//	richLabel->SetTextAttributes(3, 5, clRed, TFontStyles() << fsBold);

}


void __fastcall TFMain::WndProc(Messages::TMessage &message) {

	if (message.Msg == WM_CHAR) {
		controller->processKeystroke(message.WParam);

	}

	 /*
	wchar_t wch = iocontrol->getKeystroke(Handle, Message.Msg, Message.WParam, Message.LParam);

	if (wch) {

		if (!iocontrol->isBufferingEnabled() && wch == SPACE_BAR) {
			iocontrol->setBufferingEnabled(true);
			StartInfo->Visible = false;
		}

	//		TFont* font = TextBox->Font;
	//
	//		int size = font->Size;
	//		int color = font->Color;
	//
	//		font->Color = (color & (TColor) RGB (0xff, 0x80, 0x00)) == (TColor) RGB (0xff, 0x80, 0x00) ? clWindowText : (TColor) RGB (0xff, 0x80, 0x00);

		else if (wch) {

			TextBox->Text += UnicodeString(wch);
			Label1->Caption = iocontrol->getCharBuffer();
		}
	}

	*/

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
//
//void TFMain::RemoveCharColor(TRichEdit* richEdit, int charIndex) {
//
//	if (charIndex >= 0 && charIndex < richEdit->Text.Length())
//	{
//		richEdit->SelStart = charIndex;
//		richEdit->SelLength = 1;
//		richEdit->SelAttributes->Color = clBlack;
//
//	}
//}

void __fastcall TFMain::StartInfoClick(TObject *Sender)
{
	  controller->startPractice();
}
//---------------------------------------------------------------------------


