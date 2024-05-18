//---------------------------------------------------------------------------

#ifndef AchievementH
#define AchievementH

#include <vcl.h>
#include <vector>
//---------------------------------------------------------------------------

enum class AchievementType {
	Beginner,
    SpeedMaster,
    PerfectScore,
    FirstFive,
    LongDay,
    Count,
    Unknown
};

class Achievement {

    private:
    	static std::vector<UnicodeString> achievementTypeStrings;

    public:
        static std::vector<UnicodeString>& getAchievementTypeStrings();

};


#endif
