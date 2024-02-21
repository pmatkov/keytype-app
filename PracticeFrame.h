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

#include "Parser.h"
#include "PracticeSession.h"
#include "PracticeForm.h"
//---------------------------------------------------------------------------

enum PracticeStatus {
	Initialized,
	Started,
	Restarted,
	Resumed,
    Paused
};

class TFrPractice : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LStart;
	TRichEdit *RETextBox;
	TFrOptions *FrOptions;
	void __fastcall FrOptionsBtOptionsClick(TObject *Sender);

private:	// User declarations
	Parser* parser;
    MainSession* mainSession;
    PracticeSession* practiceSession;
    TFPractice *FPractice;

	HWND REHandle;
public:		// User declarations
	__fastcall TFrPractice(TComponent* Owner);
    __fastcall TFrPractice(TComponent* Owner, Parser *parser, PracticeSession *practiceSession);
    void setPracticeForm(TFPractice *_FPractice);
    void setPracticeStatus(PracticeStatus status);
    virtual void __fastcall WndProc(TMessage &Message);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrPractice *FrPractice;
//---------------------------------------------------------------------------
#endif
