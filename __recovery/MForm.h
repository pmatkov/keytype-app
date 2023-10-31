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

//---------------------------------------------------------------------------

class PracticeController;

class TFMain : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *TextBox;
	TLabel *Label1;
	TLabel *StartInfo;
	void __fastcall StartInfoClick(TObject *Sender);

private:	// User declarations
//	IOControl *iocontrol;
//	TextSource *textsource;

	 PracticeController* controller;
public:		// User declarations
	__fastcall TFMain(TComponent* Owner);
	 virtual void __fastcall WndProc(TMessage &Message);

	 void SetCharUnderline(TRichEdit* richEdit, int charIndex);
	 void RemoveCharUnderline(TRichEdit* richEdit, int charIndex);
	 void SetCharColor(TRichEdit* richEdit, int charIndex, TColor textColor);
//	 void RemoveCharColor(TRichEdit* richEdit, int charIndex);

};
//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------

#endif
