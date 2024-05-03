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
#include "TypingStatsFrame.h"
#include "TypingTextFrame.h"

//---------------------------------------------------------------------------
class TFrPractice : public TFrame
{
__published:	// IDE-managed Components
	TFrTypingStats *FrTypingStats;
    TFrTypingText *FrTypingText;
	TButton *BtOptions;

	void __fastcall FrOptionsBtOptionsClick(TObject *Sender);

private:	// User declarations
	Parser *parser;
    MainSession *mainSession;
    TypingSession *typingSession;
    Dictionary *dictionary;

    std::unique_ptr<TFPracticeOptions> FPracticeOptions;

public:		// User declarations
	__fastcall TFrPractice(TComponent* Owner);
    __fastcall TFrPractice(TComponent* Owner, Parser *_parser, MainSession *_mainSession, TypingSession *_typingSession);

    void processCharMessages(WPARAM wParam);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrPractice *FrPractice;
//---------------------------------------------------------------------------
#endif
