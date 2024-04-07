//---------------------------------------------------------------------------

#ifndef GameStatisticsH
#define GameStatisticsH
//---------------------------------------------------------------------------

#include <vcl.h>

class GameStatistics {

    private:
        int matchCount = 0;
        int points = 0;

    public:

        void resetStatistics();
        int getMatchCount() const;
        void setMatchCount(int _correctWords);

        int getPoints() const;
        void setPoints(int _points);
        static int calculatePoints(const UnicodeString &word);

};
#endif
