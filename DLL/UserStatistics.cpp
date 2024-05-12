//---------------------------------------------------------------------------

#pragma hdrstop

#include "UserStatistics.h"
#include "KeyStatistics.h"
#include <System.SysUtils.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rtl.lib"

UserStatistics::UserStatistics(const std::vector<TDateTime> &_practiceTime, const std::map<wchar_t, KeyStatistics> &_keyStatistics) :  practiceTime(_practiceTime), keyStatistics(_keyStatistics) {}

UserStatistics::UserStatistics(const std::map<wchar_t, KeyStatistics> &_keyStatistics) : keyStatistics(_keyStatistics) {}

const std::vector<TDateTime>& UserStatistics::getPracticeTime() const {
    return practiceTime;
}

const std::map<wchar_t, KeyStatistics>& UserStatistics::getKeyStatistics() const {
    return keyStatistics;
}

wchar_t UserStatistics::findMostAccurateChar() const {

    wchar_t mostAccurateChar = '\0';
    int compCount = 0;
    double maxAccuracy = 0;

  	for (const auto& pair : keyStatistics) {

		wchar_t key = pair.first;
    	KeyStatistics value = pair.second;

        if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
             if (std::isalpha(key)) {
                key = std::tolower(key);
             }
            double accuracy = 0;
            int count = 0;

            if (value.getCorrect() + value.getMistake() != 0) {
                accuracy = (value.getCorrect()/ (value.getCorrect() + value.getMistake())) * 100;
                count = value.getCorrect() + value.getMistake();

                if (accuracy > maxAccuracy) {
                   maxAccuracy = accuracy;
                   compCount = count;
                   mostAccurateChar = key;
                }
                else if (accuracy && accuracy == maxAccuracy && count > compCount) {
                  compCount = count;
                  mostAccurateChar = key;
                }
            }
        }
  	}
  	return mostAccurateChar;
}

wchar_t UserStatistics::findLeastAccurateChar() const {

    wchar_t leastAccurateChar = '\0';
    int compCount = INT_MAX;
    double minAccuracy = 100;

  	for (const auto& pair : keyStatistics) {

		wchar_t key = pair.first;
    	KeyStatistics value = pair.second;

        if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
             if (std::isalpha(key)) {
                key = std::tolower(key);
             }

            double accuracy = 100;
            int count = 0;

            if (value.getCorrect() + value.getMistake() != 0) {
                accuracy = (value.getCorrect()/ (value.getCorrect() + value.getMistake())) * 100;
                count = value.getCorrect() + value.getMistake();

                if (accuracy < minAccuracy) {
                    minAccuracy = accuracy;
                    compCount = count;
                    leastAccurateChar = key;
                }
                else if (accuracy < 100 && accuracy == minAccuracy && count < compCount) {
                  compCount = count;
                  leastAccurateChar = key;
                }
            }
        }

  	}
  	return leastAccurateChar;
}

double UserStatistics::calculateAvgPracticeTime() const {

	double totalMin = 0;

  	for (const TDateTime &pt : practiceTime) {

    	unsigned short hrs, min, sec, msec;
       	Sysutils::DecodeTime(pt, hrs, min, sec, msec);

        totalMin += hrs * 60 + min + sec / 60.0;
  	}

    if (practiceTime.size() > 0) {
        return totalMin / practiceTime.size();
    }

    return 0.0;
}

void UserStatistics::Destroy()  {
    delete this;
}


UserStatistics* CreateUserStatistics(const std::vector<TDateTime> &practiceTime, const std::map<wchar_t, KeyStatistics> &keyStatistics) {
    return new UserStatistics(practiceTime, keyStatistics);
}
