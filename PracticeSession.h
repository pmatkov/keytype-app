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
		int mistakes;

	public:
		const User &getUser() const;
		void setUser(const User& _user);

		const TextSource &getTextsource() const;
		void setTextsource(const TextSource& _textsource);

		void increaseCurrentCharIndex();
        void decreaseCurrentCharIndex();

		const int getMistakes() const;
		void setMisttakes(int _mistakes);

};

#endif
