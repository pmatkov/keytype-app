//---------------------------------------------------------------------------

#ifndef TypingSessionH
#define TypingSessionH
//---------------------------------------------------------------------------

#include<map>

#include "Session.h"
#include "TextSource.h"
#include "KeyStatistics.h"

enum SessionStatus {
	Initialized,
	Started,
	Restarted,
	Resumed,
    Paused
};


class TypingSession : public Session {

	private:
		TextSource textSource;

        std::map<wchar_t, KeyStatistics> keyStatistics;

        int totalWords = 0;
        int totalChars = 0;

        int typedWords = 0;
		int mistakes = 0;

        SessionStatus sessionStatus;

	public:
    	TypingSession();

		const TextSource& getTextSource() const;
		void setTextSource(const TextSource& _textSource);

		void increaseCharIndex();
		void decreaseCharIndex();

        int getTotalWords() const;
		int getTotalChars() const;
		void setTotalChars(int _totalChars);
		void incTotalChars();

        void increaseTypedWords();

		int getMistakes() const;
		void setMistakes(int _mistakes);
		void increaseMistakes();

        double getAccuracy() const;
        double calculateAccuracy() const;

        double getSpeed() const;
        double calculateSpeed() const;

        const SessionStatus& getSessionStatus() const;
        void setSessionStatus(const SessionStatus &_sessionStatus);

};

#endif
