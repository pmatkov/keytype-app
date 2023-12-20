//---------------------------------------------------------------------------

#include "UIUtils.h"

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)


void UIUtils::setCharStyle(TRichEdit* richedit, int charIndex, TFontStyle style, bool enabled) {

	if (charIndex >= 0 && charIndex < richedit->Text.Length()) {

		richedit->SelStart = charIndex;
		richedit->SelLength = 1;

		if (enabled)
			richedit->SelAttributes->Style = richedit->SelAttributes->Style << style;
		else
		  richedit->SelAttributes->Style = richedit->SelAttributes->Style >> style;
	}
}

void UIUtils::setCharColor(TRichEdit* richedit, int charIndex, TColor textColor) {

	if (charIndex >= 0 && charIndex < richedit->Text.Length()) {

		richedit->SelStart = charIndex;
		richedit->SelLength = 1;
		richedit->SelAttributes->Color = textColor;
	}
}

void UIUtils::setTextColor(TRichEdit* richedit, TColor textColor) {

	richedit->SelStart = 0;
	richedit->SelLength = richedit->Text.Length();
	richedit->SelAttributes->Color = textColor;
}


void UIUtils::enableChildControls(TWinControl* parent)
{
    for (int i = 0; i < parent->ControlCount; i++) {

    	TControl* child = parent->Controls[i];
    	child->Enabled = true;
    }
}

void UIUtils::disableChildControls(TWinControl* parent)
{
    for (int i = 0; i < parent->ControlCount; i++) {

    	TControl* child = parent->Controls[i];
    	child->Enabled = false;
    }
}



