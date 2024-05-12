//---------------------------------------------------------------------------

#ifndef TypingSessionH
#define TypingSessionH
//---------------------------------------------------------------------------

#include<map>
#include<vector>

#include "Session.h"
#include "TextSource.h"
#include "KeyStatistics.h"

enum SessionStatus {
	Initialized,
	Started,
	Restarted,
	Resumed,
    Paused,
    Completed,
    Cleared
};

enum LessonGoal {
	lSpeed,
	lAccuracy,
    Count,
	Unknown
};


class TypingSession : public Session {

	private:
		TextSource textSource;
        UnicodeString instructions;

        int charCount;
        int wordCount;

        std::vector<double> speedReadings;
        std::map<wchar_t, KeyStatistics> keyStatistics;

        int typedWords = 0;
		int mistakes = 0;

        SessionStatus sessionStatus;

        LessonGoal lessonGoal;
        int goalValue;
        int difficulty;

        static std::vector<UnicodeString> lessonGoalStrings;

	public:
    	TypingSession();

		const TextSource& getTextSource() const;
		void setTextSource(const TextSource& _textSource);

        int getCharCount() const;
        void setCharCount(int _charCount);
        int getWordCount() const;
        void setWordCount(int _wordCount);

        void increaseCorrectKey(wchar_t key);
        void increaseMistakeKey(wchar_t key);
        std::map<wchar_t, KeyStatistics> &getKeyStatistics();

		void increaseCharIndex();
		void decreaseCharIndex();

        void increaseTypedWords();

		int getMistakes() const;
		void setMistakes(int _mistakes);
		void increaseMistakes();

        double getAccuracy();
        double calculateAccuracy();

        double getSpeed();
        double getAvgSpeed();
        double calculateSpeed();

        const SessionStatus& getSessionStatus() const;
        void setSessionStatus(const SessionStatus &_sessionStatus);

        const LessonGoal& getLessonGoal() const;
        void setLessonGoal(const LessonGoal &_lessonGoal);

       	int getGoalValue() const;
        void setGoalValue(int _goalValue);

        int getDifficulty() const;
        void setDifficulty(int _difficulty);

        void resetSessionData();

        const std::vector<UnicodeString>& getLessonGoalStrings();

};

#endif
