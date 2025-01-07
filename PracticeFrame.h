//---------------------------------------------------------------------------

#ifndef PracticeFrameH
#define PracticeFrameH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "KeyboardFrame.h"
#include "TypingStatsFrame.h"
#include "TypingTextFrame.h"

#include <memory>
#include <vector>

#include "KeyboardFrame.h"
#include "TypingStatsFrame.h"
#include "TypingTextFrame.h"
#include "PracticeSourceForm.h"

#include "Parser.h"
#include "MainSession.h"
#include "TypingSession.h"
#include "DataModule.h"
#include "AuthenticationService.h"

//---------------------------------------------------------------------------

class TFrPractice : public TFrame
{
__published:    // IDE-managed Components
    TPanel *PPracticeType;
    TPanel *PPracticeLimit;
    TSpeedButton *SBtPracticeType1;
    TSpeedButton *SBtPracticeType2;
    TSpeedButton *SBtPracticeLimit1;
    TSpeedButton *SBtPracticeLimit2;
    TSpeedButton *SBtPracticeLimit3;
    TSpeedButton *SBtPracticeLimit4;

	TBitBtn *BtConfig;
	TButton *BtStartQuit;
    TLabel *LPracticeResult;
    TLabel *LPracticeResultDisplay;

	TFrTypingStats *FrTypingStats;
	TFrTypingText *FrTypingText;
	TFrKeyboard *FrKeyboard;
	TLabel *LKeyboardLayout;

    void __fastcall BtStartQuitClick(TObject *Sender);
    void __fastcall BtConfigClick(TObject *Sender);

private:    // User declarations
    Parser *parser;
    MainSession *mainSession;
    TypingSession *typingSession;
    TDataModule1 *dataModule;
    AuthenticationService *authService;

    std::unique_ptr<TFPracticeSource> FPracticeSource;

public:     // User declarations
    __fastcall TFrPractice(TComponent* Owner);
    __fastcall TFrPractice(TComponent* Owner, Parser *_parser, MainSession *_mainSession, TypingSession *_typingSession, TDataModule1 *_dataModule, AuthenticationService *_authService);

    void setTextSource(const std::vector<UnicodeString> &wordList, int minChars, int maxChars, int minWords, int maxWords);
    void assignPNGToBtn(TBitBtn *button, const UnicodeString &path);

    void highlightKey(wchar_t wch, bool keyDown);

    void processCharMessages(WPARAM wParam);
    virtual void __fastcall WndProc(TMessage &Message);

};

//---------------------------------------------------------------------------
extern PACKAGE TFrPractice *FrPractice;
//---------------------------------------------------------------------------
#endif
