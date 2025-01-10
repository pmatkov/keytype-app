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

        int wordCount;
        int charCount;

        double accuracy = 100;
        double speed = 0;

        std::map<wchar_t, KeyStatistics> keyStatistics;

        std::vector<double> speedReadings;

        int typedWords = 0;
		int mistakes = 0;

        SessionStatus sessionStatus;
        SessionType sessionType;

        LessonGoal lessonGoal;
        int goalValue;
        int difficulty;

        bool virtualKeyboardVisible = false;

        static std::vector<UnicodeString> sessionStatusStrings;
        static std::vector<UnicodeString> sessionTypeStrings;
        static std::vector<UnicodeString> lessonGoalStrings;

	public:
    	TypingSession();

		const TextSource& getTextSource() const;
		void setTextSource(const TextSource& _textSource);

        int getWordCount() const;
        void setWordCount(int _wordCount);
        int getCharCount() const;
        void setCharCount(int _charCount);

        double getAccuracy();
        void calculateAccuracy();

        double getSpeed();
        double getAvgSpeed();
        void calculateSpeed();

        void increaseCorrectKey(wchar_t key);
        void increaseMistakeKey(wchar_t key);
        std::map<wchar_t, KeyStatistics> &getKeyStatistics();

		void increaseCharIndex();
		void decreaseCharIndex();

        void increaseTypedWords();

		int getMistakes() const;
		void setMistakes(int _mistakes);
		void increaseMistakes();

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

        void setVirtualKeyboardVisible(bool _virtualKeyboardVisible);
        bool isVirtualKeyboardVisible();

        void initializeSession();
        void resetSession();

        const std::vector<UnicodeString>& getSessionStatusStrings();
        const std::vector<UnicodeString>& getSessionTypeStrings();
        const std::vector<UnicodeString>& getLessonGoalStrings();

};

#endif
