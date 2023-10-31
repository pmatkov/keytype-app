//---------------------------------------------------------------------------

#pragma hdrstop

#include "PracticeController.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

PracticeController::PracticeController(TFMain* _form) : form(_form) {}

void PracticeController::startPractice() {

	form->TextBox->Lines->Add(session.getTextsource().getText());
	form->SetCharUnderline(form->TextBox, 0);

	ioControl.setBufferingEnabled(true);
}

void PracticeController::processKeystroke(WPARAM wParam) {

	wchar_t wch = ioControl.getChar(wParam);

	if (wch) {

		form->TextBox->Perform(WM_SETREDRAW, 0, 0);

		if (wch == session.getTextsource().getCurrentChar()) {

			form->RemoveCharUnderline(form->TextBox, session.getTextsource().getCurrentCharIndex()-1);
			form->SetCharColor(form->TextBox, session.getTextsource().getCurrentCharIndex()-1, clSilver);

			session.increaseCurrentCharIndex();

			form->SetCharUnderline(form->TextBox, session.getTextsource().getCurrentCharIndex()-1);

		}
		else {

			form->RemoveCharUnderline(form->TextBox, session.getTextsource().getCurrentCharIndex()-1);
			form->SetCharColor(form->TextBox, session.getTextsource().getCurrentCharIndex()-1, clRed);
		}

		form->TextBox->Perform(WM_SETREDRAW, 1, 0);
		form->TextBox->Invalidate();

	}

	/*
	// Get the updated buffer from IOControl
	UnicodeString buffer = ioControl.GetBuffer();

	// Compare the buffer with the practice text and update the view
	view->UpdateTextColors(buffer);

    */
}


