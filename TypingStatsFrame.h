//---------------------------------------------------------------------------

#ifndef TypingStatsFrameH
#define TypingStatsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "MainSession.h"
#include "TypingSession.h"
//---------------------------------------------------------------------------
class TFrTypingStats : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LTime;
	TLabel *LDisplayTime;
	TLabel *LSpeed;
	TLabel *LDisplaySpeed;
	TLabel *LAccuracy;
	TLabel *LDisplayAccuracy;
	TTimer *TStatsTimer;
    void __fastcall TStatsTimerTimer(TObject *Sender);
private:	// User declarations
	MainSession *mainSession;
    TypingSession *typingSession;
public:		// User declarations
	__fastcall TFrTypingStats(TComponent* Owner);

    void setMainSession(MainSession *_mainSession);
    void setTypingSession(TypingSession *_typingSession);

    void displayStatsItems();
    void hideStatsItems();

    void clearTimerDisplay();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrTypingStats *FrTypingStats;
//---------------------------------------------------------------------------
#endif
