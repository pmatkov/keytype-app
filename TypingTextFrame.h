//---------------------------------------------------------------------------

#ifndef TypingTextFrameH
#define TypingTextFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include "MainSession.h"
#include "TypingSession.h"
#include "Parser.h"
#include "TypingStatsFrame.h"
//---------------------------------------------------------------------------
class TFrTypingText : public TFrame
{
__published:	// IDE-managed Components
	TRichEdit *REText;
	TLabel *LPrompt;
private:	// User declarations
	MainSession *mainSession;
    TypingSession *typingSession;
    Parser *parser;

    TFrTypingStats *FrTypingStats;

    HWND REHandle;
public:		// User declarations
	__fastcall TFrTypingText(TComponent* Owner);

    void setMainSession(MainSession *_mainSession);
    void setTypingSession(TypingSession *_typingSession);
    void setParser(Parser *_parser);
    void setFrameTypingStats(TFrTypingStats *_FrTypingStats);

    void changeSessionView(SessionStatus status);
    void changeSessionStatus(SessionStatus status);
    void initializeTypingStats();
    void resetTypingStats();

    void processCharMessages(WPARAM wParam);
    void moveCaret(CaretType caretType, int index);
    void clearCaret(CaretType caretType, int index);
	void setCaret(CaretType caretType, int index);

    static LRESULT CALLBACK RESubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

    void __fastcall (__closure *OnLessonComplete)(TObject *Sender);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrTypingText *FrTypingText;
//---------------------------------------------------------------------------
#endif
