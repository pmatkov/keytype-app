//---------------------------------------------------------------------------

#ifndef PracticeFrameH
#define PracticeFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "OptionsFrame.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

enum StartControl {
	Initial,
	Start,
	Restart,
	Resume,
    Pause
};

class TFrPractice : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LStart;
	TRichEdit *RETextBox;
	TFrOptions *FrOptions;
	void __fastcall FrOptionsBtOptionsClick(TObject *Sender);

private:	// User declarations

	HWND REHandle;
public:		// User declarations
	__fastcall TFrPractice(TComponent* Owner);
    void setStatusInfo(StartControl status);
     virtual void __fastcall WndProc(TMessage &Message);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrPractice *FrPractice;
//---------------------------------------------------------------------------
#endif
