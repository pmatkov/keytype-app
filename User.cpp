//---------------------------------------------------------------------------

#pragma hdrstop

#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


User::User() {}

User::User(const UnicodeString &_username, bool _isLoggedIn) : username(_username), isLoggedIn(_isLoggedIn) {}

User::User(const UnicodeString &_name, const UnicodeString &_surname, int _age, const UnicodeString &_username, const UnicodeString &_email) :
			 name(_name), surname(_surname), age(_age), username(_username), email(_email) {}


const UnicodeString& User::getName() const {
	return name;
}

void User::setName(const UnicodeString &_name) {
	name = _name;
}

const UnicodeString& User::getSurname() const {
	return surname;
}

int User::getAge() const {
	return age;
}

void User::setSurname(const UnicodeString &_surname) {
	surname = _surname;
}

void User::setAge(int _age) {
	age = _age;
}

const UnicodeString & User::getUsername() const {
	return username;
}

void User::setUsername(const UnicodeString &_username) {
	username = _username;
}


const UserType& User::getUserType() const {
	   return userType;
}

void User::setUserType(const UserType &_userType) {
	userType = _userType;
}

bool User::getIsLoggedIn() const {
   return  isLoggedIn;
}
void User::setIsLoggedIn(bool _isLoggedIn) {
	 isLoggedIn = _isLoggedIn;
}


