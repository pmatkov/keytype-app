//---------------------------------------------------------------------------

#ifndef Lessons2FrameH
#define Lessons2FrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "OptionsFrame.h"
#include "PracticeFrame.h"
#include <Vcl.ExtCtrls.hpp>
#include <vcl.h>

#include "Parser.h"
#include "MainSession.h"
#include "TypingSession.h"
#include "AuthenticationService.h"
#include "DataModule.h"

#include "TypingStatsFrame.h"
#include "TypingTextFrame.h"
//---------------------------------------------------------------------------
class TFrLessons2 : public TFrame
{
__published:	// IDE-managed Components
	TComboBox *CBSelectCourse;
	TComboBox *CBSelectLesson;
	TLabel *LChars;
	TLabel *LWords;
	TLabel *LCharsDisplay;
	TLabel *LWordsDisplay;
	TLabel *LGoal;
	TLabel *LGoalDisplay;
	TFrTypingStats *FrTypingStats;
	TLabel *LDifficulty;
	TLabel *LDifficultyDisplay;
	TMemo *MInstructions;
	TFrTypingText *FrTypingText;
	TButton *BtStartQuit;
	TLabel *LLessonResult;
	TLabel *LLessonResultDisplay;
	void __fastcall CBSelectCourseChange(TObject *Sender);
	void __fastcall CBSelectLessonChange(TObject *Sender);
	void __fastcall BtStartQuitClick(TObject *Sender);
private:	// User declarations
	Parser *parser;
    MainSession *mainSession;
    TypingSession *typingSession;
    AuthenticationService *authService;
    TDataModule1 *dataModule;

    std::vector<std::pair<int, UnicodeString>> coursesValues;
    std::vector<std::pair<int, UnicodeString>> lessonsValues;

public:		// User declarations
	__fastcall TFrLessons2(TComponent* Owner);
    __fastcall TFrLessons2(TComponent* Owner, Parser *_parser, MainSession *_mainSession, TypingSession *_typingSession, AuthenticationService *_authService, TDataModule1 *_dataModule);

    void hideInterfaceValues();
    bool setTextSource(int index);

    void __fastcall FrTypingTextTypingComplete(TObject *Sender);

    void processCharMessages(WPARAM wParam);
   	virtual void __fastcall WndProc(TMessage &Message);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrLessons2 *FrLessons2;
//---------------------------------------------------------------------------
#endif
