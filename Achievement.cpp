//---------------------------------------------------------------------------

#pragma hdrstop

#include "Achievement.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

std::vector<UnicodeString> Achievement::achievementTypeStrings = {"Beginner", "SpeedMaster", "PerfectScore", "FirstFive", "LongDay"};

std::vector<UnicodeString>& Achievement::getAchievementTypeStrings() {
    return achievementTypeStrings;
}

