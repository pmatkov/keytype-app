//---------------------------------------------------------------------------

#ifndef PracticeFrameH
#define PracticeFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <vcl.h>
#include <windows.h>

#include "PracticeOptionsForm.h"
#include "OptionsFrame.h"

#include "Parser.h"
#include "MainSession.h"
#include "TypingSession.h"
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TFrPractice : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LStart;
	TRichEdit *RETextBox;
	TFrOptions *FrOptions;
	TLabel *LTime;
	TLabel *LDisplayTime;
	TTimer *Timer1;
	TLabel *LSpeed;
	TLabel *LDisplaySpeed;
	TLabel *LAccuracy;
	TLabel *LDisplayAccuracy;
	void __fastcall FrOptionsBtOptionsClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);

private:	// User declarations
	Parser *parser;
    MainSession *mainSession;
    TypingSession *typingSession;

    std::unique_ptr<TFPracticeOptions> FPracticeOptions;
	HWND REHandle;

    int maxChars;
public:		// User declarations
	__fastcall TFrPractice(TComponent* Owner);
    __fastcall TFrPractice(TComponent* Owner, Parser *_parser, MainSession *_mainSession, TypingSession *_typingSession);

    void setPracticeStatus(SessionStatus status);
    void displayStatsItems();
    void hideStatsItems();

    virtual void __fastcall WndProc(TMessage &Message);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrPractice *FrPractice;
//---------------------------------------------------------------------------
#endif
