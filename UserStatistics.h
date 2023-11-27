//---------------------------------------------------------------------------

#ifndef UserStatisticsH
#define UserStatisticsH
//---------------------------------------------------------------------------
#include<vcl.h>
#include<vector>
#include<map>

#include "KeyPerformance.h"

class UserStatistics {

	private:
		int points;
		int speed;
		int accuracy;
		int coverage;
		TDateTime practiceTime;
		std::vector<TDateTime> practiceDays;
		std::map<wchar_t, KeyPerformance> keyPerformance;
};

#endif
