//---------------------------------------------------------------------------

#ifndef PracticeSessionH
#define PracticeSessionH
//---------------------------------------------------------------------------
#include "User.h"
#include "TextSource.h"

class PracticeSession {

	private:
		User user;
		TextSource textsource;
		bool mistake;
		int mistakesCount;
		bool paused;

	public:
		const User& getUser() const;
		void setUser(const User& _user);

		const TextSource& getTextsource() const;
		void setTextsource(const TextSource& _textsource);

		void increaseCharIndex();
		void decreaseCharIndex();

		const bool& isMistake() const;
		void setMistake(bool _mistake);

		const int& getMistakesCount() const;
		void setMistakesCount(int _mistakesCount);

		const bool isPaused() const;
		void setPaused(bool _paused);


};

#endif
