//---------------------------------------------------------------------------

#ifndef PracticeFrameH
#define PracticeFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include "OptionsFrame.h"
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

    int maxChars;
public:		// User declarations
	__fastcall TFrPractice(TComponent* Owner);
    __fastcall TFrPractice(TComponent* Owner, Parser *parser, PracticeSession *practiceSession);
    void setPracticeForm(TFPractice *_FPractice);
    void setPracticeStatus(PracticeStatus status);
    int countMaxChars(TRichEdit *RETextBox, const UnicodeString &string);
    int estimateMaxChars(TRichEdit *RETextBox);
    virtual void __fastcall WndProc(TMessage &Message);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrPractice *FrPractice;
//---------------------------------------------------------------------------
#endif
