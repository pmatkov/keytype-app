//---------------------------------------------------------------------------

#ifndef PracticeSessionH
#define PracticeSessionH
//---------------------------------------------------------------------------
#include "Session.h"
#include "TextSource.h"
#include "KeyStatistics.h"

class PracticeSession : public Session {

	private:
		TextSource textSource;

		bool mistake = false;
        KeyStatistics keyStatistics;

		bool ignoreSeqMistakes;
		bool stopOnMistake;

		bool active;
		bool paused;

	public:
    	PracticeSession();

		const TextSource& getTextSource() const;
		void setTextSource(const TextSource& _textSource);

		void increaseCharIndex();
		void decreaseCharIndex();

		const bool& isMistake() const;
		void setMistake(bool _mistake);

		const int& getTotalCount() const;
		void setTotalCount(int _totalCount);
		void incTotalCount();

		const int& getCorrectCount() const;
		void setCorrectCount(int _correctCount);
		void incCorrectCount();

		const int& getMistakesCount() const;
		void setMistakesCount(int _mistakesCount);
		void incMistakesCount();

		const bool doIgnoreSeqMistakes() const;
		void setIgnoreSeqMistakes(bool _ignoreSeqMistakes);
		const bool isStopOnMistake() const;
		void setStopOnmistake(bool _stopOnMistake);

		const bool isActive() const;
		void setActive(bool _active);
		const bool isPaused() const;
		void setPaused(bool _paused);


};

#endif
