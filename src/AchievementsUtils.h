//---------------------------------------------------------------------------

#ifndef AchievementsUtilsH
#define AchievementsUtilsH

#include <vector>
#include "Achievement.h"

#include "AchievementsHeader.h"
#include "AchievementsRecord.h"

//---------------------------------------------------------------------------

namespace AchievementsUtils {

    void saveToFile(const AchievementsHeader &header, const std::vector<AchievementsRecord> &records, const UnicodeString &path);
    std::vector<AchievementsRecord> readFromFile(const UnicodeString &path);
    std::vector<AchievementsRecord> filterAchievements(const std::vector<AchievementsRecord> &records, int idUser = 0, AchievementType type = AchievementType::Unknown);
}

#endif
