//---------------------------------------------------------------------------

#ifndef PracticeSessionH
#define PracticeSessionH
//---------------------------------------------------------------------------
#include "User.h"
#include "TextSource.h"

class PracticeSession {

	private:
		User user;
		TextSource textSource;
		bool mistake;
		int totalCount = 0;
		int validCount = 0;
		int mistakesCount = 0;
		bool ignoreSeqMistakes;
		bool stopOnMistake;
		bool active;
		bool paused;

	public:
		const User& getUser() const;
		void setUser(const User& _user);

		const TextSource& getTextSource() const;
		void setTextSource(const TextSource& _textSource);

		void increaseCharIndex();
		void decreaseCharIndex();

		const bool& isMistake() const;
		void setMistake(bool _mistake);

		const int& getTotalCount() const;
		void setTotalCount(int _totalCount);
		void incTotalCount();
		const int& getValidCount() const;
		void setValidCount(int _validCount);
		void incValidCount();
		const int& getMistakesCount() const;
		void setMistakesCount(int _mistakesCount);
		void incMistakesCount();

		const bool isIgnoreSeqMistakes() const;
		void setIgnoreSeqMistakes(bool _ignoreSeqMistakes);
		const bool isStopOnMistake() const;
		void setStopOnmistake(bool _stopOnMistake);

		const bool isActive() const;
		void setActive(bool _active);
		const bool isPaused() const;
		void setPaused(bool _paused);


};

#endif
