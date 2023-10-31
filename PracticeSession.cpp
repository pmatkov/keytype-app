//---------------------------------------------------------------------------

#pragma hdrstop

#include "PracticeSession.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


const User &PracticeSession::getUser() const {
	return user;
}
void PracticeSession::setUser(const User& _user) {
   user = _user;
}

const TextSource &PracticeSession::getTextsource() const {
	return textsource;
}
void PracticeSession::setTextsource(const TextSource& _textsource) {
	textsource = _textsource;
}

void PracticeSession::increaseCurrentCharIndex() {
     textsource.increaseCurrentCharIndex();
}

void PracticeSession::decreaseCurrentCharIndex() {
	 textsource.decreaseCurrentCharIndex();
}

const int PracticeSession::getMistakes() const {
	return mistakes;
}
void PracticeSession::setMisttakes(int _mistakes) {

     mistakes = _mistakes;
}