//---------------------------------------------------------------------------

#ifndef MFormH
#define MFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "IOControl.h"
#include "PracticeController.h"
#include "OptionsFrame.h"
#include <Vcl.Forms.hpp>

//---------------------------------------------------------------------------

class PracticeController;

class TFMain : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *TextBox;
	TLabel *StartLabel;
	TFrame1 *Frame11;

//	void __fastcall StartLabelClick(TObject *Sender);

private:	// User declarations
	IOControl *iocontrol;
	PracticeSession *session;
	PracticeController* controller;
public:		// User declarations
	__fastcall TFMain(TComponent* Owner);
	 virtual void __fastcall WndProc(TMessage &Message);

	 void SetCharUnderline(TRichEdit* richEdit, int charIndex);
	 void RemoveCharUnderline(TRichEdit* richEdit, int charIndex);
	 void SetCharColor(TRichEdit* richEdit, int charIndex, TColor textColor);
	 void SetTextColor(TRichEdit* richEdit, TColor textColor);

};
//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------

#endif
