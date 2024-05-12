//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.SysUtils.hpp>
#pragma hdrstop

#include "StatisticsForm.h"
#include "UserStatistics.h"
#include "KeyStatistics.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFStatistics *FStatistics;
//---------------------------------------------------------------------------
__fastcall TFStatistics::TFStatistics(TComponent* Owner) : TForm(Owner) {}
__fastcall TFStatistics::TFStatistics(TComponent* Owner, UserStatistics *_userStatistics) : TForm(Owner) {

    if (_userStatistics) {
        userStatistics = _userStatistics;

        std::vector<TDateTime> practiceTime = userStatistics->getPracticeTime();
    	std::map<wchar_t, KeyStatistics> keyStatistics = userStatistics->getKeyStatistics();

        int skip = practiceTime.size() <= 10 ? 1 : round(practiceTime.size()/ 10);

        for (int i = 0; i < practiceTime.size(); i += skip) {

            unsigned short year, month, day;
            unsigned short hrs, min, sec, msec;

            DecodeDate(practiceTime[i], year, month, day);
            DecodeTime(practiceTime[i], hrs, min, sec, msec);

            double totalMinutes = hrs * 60 + min + sec / 60.0;

            STime->XValues->DateTime = true;
            STime->AddXY(EncodeDate(year, month, day), totalMinutes);
        }


        for (const auto& pair : keyStatistics) {
            SCorrect->AddY(pair.second.getCorrect(), UnicodeString(pair.first));
            SMistake->AddY(pair.second.getMistake(), UnicodeString(pair.first));
        }

        LMostAccurateCharDisplay->Caption = userStatistics->findMostAccurateChar();
        LLeastAccurateCharDisplay->Caption = userStatistics->findLeastAccurateChar();
        LAveragePracticeTimeDisplay->Caption = FormatFloat("0.00", userStatistics->calculateAvgPracticeTime()) + " min";
    }
}

void CreateStatisticsForm(UserStatistics *userStatistics) {

    TFStatistics *FStatistics = new TFStatistics(nullptr, userStatistics);
    FStatistics->Position = poMainFormCenter;
    FStatistics->ShowModal();
    delete FStatistics;
}


