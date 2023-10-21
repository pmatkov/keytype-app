//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "TextUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

// add typed characters to the text control
void __fastcall TForm1::WndProc(Messages::TMessage &Message)
{
	char ch = TextUtils::getDisplayableChar(Handle, Message.Msg, Message.WParam, Message.LParam);

	if (ch) {

		TFont* font = PracticeText->Font;

		int size = font->Size;
		int color = font->Color;

		font->Color = (color & (TColor) RGB (0xff, 0x80, 0x00)) == (TColor) RGB (0xff, 0x80, 0x00) ? clWindowText : (TColor) RGB (0xff, 0x80, 0x00);

		UnicodeString str = PracticeText->Text;
		str += UnicodeString(ch);
		PracticeText->Text = str;
	}

	TForm::WndProc(Message);
}

