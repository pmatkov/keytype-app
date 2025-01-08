//---------------------------------------------------------------------------

#ifndef StatisticsFormH
#define StatisticsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>

#include "UserStatistics.h"

#if EXPORTS
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

class UserStatistics;

//---------------------------------------------------------------------------
class TFStatistics : public TForm
{

__published:	// IDE-managed Components
	TChart *ChPracticeTime;
	TChart *ChAccuracyChar;
	TBarSeries *SCorrect;
	TBarSeries *SMistake;
	TLabel *LMostAccurateChar;
	TLabel *LMostAccurateCharDisplay;
	TLabel *LLeastAccurateChar;
	TLabel *LLeastAccurateCharDisplay;
	TLabel *LAveragePracticeTime;
	TLabel *LAveragePracticeTimeDisplay;
	TBarSeries *STime;
private:	// User declarations
    UserStatistics *userStatistics;
public:		// User declarations
	__fastcall TFStatistics(TComponent* Owner);
    __fastcall TFStatistics(TComponent* Owner, UserStatistics *_userStatistics);
};

extern "C" void DLL_EXPORT __stdcall CreateStatisticsForm(UserStatistics *userStatistics);
extern PACKAGE TFStatistics *FStatistics;
//---------------------------------------------------------------------------
#endif
