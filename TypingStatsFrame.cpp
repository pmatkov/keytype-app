//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TypingStatsFrame.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrTypingStats *FrTypingStats;
//---------------------------------------------------------------------------
__fastcall TFrTypingStats::TFrTypingStats(TComponent* Owner)
	: TFrame(Owner) {}

void TFrTypingStats::setMainSession(MainSession *_mainSession) {
   mainSession = _mainSession;
}

void TFrTypingStats::setTypingSession(TypingSession *_typingSession) {
   typingSession = _typingSession;
}

void TFrTypingStats::displayStatsItems() {

	LTime->Visible = true;
    LDisplayTime->Visible = true;
    LTime->Font->Color = clGray;
	LDisplayTime->Font->Color = clSilver;

    if (mainSession->getTypingSettings().getDisplaySpeed()) {
        LSpeed->Visible = true;
        LDisplaySpeed->Visible = true;
        LSpeed->Font->Color = clGray;
        LDisplaySpeed->Font->Color = clSilver;
    }

    if (mainSession->getTypingSettings().getDisplayAccuracy()) {
        LAccuracy->Visible = true;
        LDisplayAccuracy->Visible = true;
        LAccuracy->Font->Color = clGray;
        LDisplayAccuracy->Font->Color = clSilver;
    }
}

void TFrTypingStats::hideStatsItems() {
	LTime->Visible = false;
    LDisplayTime->Visible = false;

    LSpeed->Visible = false;
    LDisplaySpeed->Visible = false;

    LAccuracy->Visible = false;
	LDisplayAccuracy->Visible = false;
}

void TFrTypingStats::clearTimerDisplay() {
	LDisplayTime->Caption = FormatDateTime("hh:nn:ss", EncodeTime(0, 0, 0, 0));
    LDisplaySpeed->Caption = FormatFloat("0.00", 0) + " WPM";
    LDisplayAccuracy->Caption = FormatFloat("0.00", 0) + " %";
}

void __fastcall TFrTypingStats::TStatsTimerTimer(TObject *Sender)
{

    int min = typingSession->getElapsedTime()/ 60;
    int sec = typingSession->getElapsedTime()% 60;
    TDateTime elapsedTime = System::Sysutils::EncodeTime(0, min, sec, 0);


    LDisplayTime->Caption = FormatDateTime("hh:nn:ss", elapsedTime);

    if (mainSession->getTypingSettings().getDisplaySpeed()) {
       LDisplaySpeed->Caption = FormatFloat("0.00", typingSession->getSpeed()) + " WPM";
    }
    if (mainSession->getTypingSettings().getDisplayAccuracy()) {
       LDisplayAccuracy->Caption = FormatFloat("0.00", typingSession->getAccuracy()) + " %";
    }

}

