//---------------------------------------------------------------------------

#ifndef FlyingWordsStatsFrameH
#define FlyingWordsStatsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrFlyingWordsStats : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LLastWord;
	TLabel *LLastWordDisplay;
	TLabel *LTimeRemaining;
	TLabel *LTimeRemainingDisplay;
	TLabel *LMatchCount;
	TLabel *LPointsDisplay;
	TLabel *LPoints;
	TLabel *LMatchCountDisplay;
	TTimer *TMsgDisplayTimer;
private:	// User declarations
public:		// User declarations
	__fastcall TFrFlyingWordsStats(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrFlyingWordsStats *FrFlyingWordsStats;
//---------------------------------------------------------------------------
#endif
