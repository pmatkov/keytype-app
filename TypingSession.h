//---------------------------------------------------------------------------

#ifndef TypingSessionH
#define TypingSessionH
//---------------------------------------------------------------------------

#include<map>
#include<vector>

#include "Session.h"
#include "TextSource.h"
#include "KeyStatistics.h"

enum class SessionStatus {
	Initialized,
	Started,
    Completed,
    Reset,
    Count,
    Unknwown
};

enum class SessionType {
	Practice,
    Lesson,
    Count,
	Unknown
};


enum class LessonGoal {
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

        double speed = 0;
        double accuracy = 100;

        std::vector<double> speedReadings;
        std::map<wchar_t, KeyStatistics> keyStatistics;

        int typedWords = 0;
		int mistakes = 0;

        SessionStatus sessionStatus;
        SessionType sessionType;

        LessonGoal lessonGoal;
        int goalValue;
        int difficulty;

        static std::vector<UnicodeString> sessionStatusStrings;
        static std::vector<UnicodeString> sessionTypeStrings;
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
        void calculateAccuracy();

        double getSpeed();
        double getAvgSpeed();
        void calculateSpeed();

        const SessionStatus& getSessionStatus() const;
        void setSessionStatus(const SessionStatus &_sessionStatus);

    	const SessionType& getSessionType() const;
        void setSessionType(const SessionType &_sessionType);

        const LessonGoal& getLessonGoal() const;
        void setLessonGoal(const LessonGoal &_lessonGoal);

       	int getGoalValue() const;
        void setGoalValue(int _goalValue);

        int getDifficulty() const;
        void setDifficulty(int _difficulty);

        void initializeSession();
        void resetSession();

        const std::vector<UnicodeString>& getSessionStatusStrings();
        const std::vector<UnicodeString>& getSessionTypeStrings();
        const std::vector<UnicodeString>& getLessonGoalStrings();

};

#endif
