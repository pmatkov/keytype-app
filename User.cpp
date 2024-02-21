//---------------------------------------------------------------------------

#pragma hdrstop

#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


User::User() {
    userType = Guest;
}

User::User(const UnicodeString &_id, const UnicodeString &_username, const UnicodeString &_name, const UnicodeString &_surname, int _age,  const UnicodeString &_email) :
id (_id), username(_username), name(_name), surname(_surname), age(_age), email(_email) {
	userType = Registered;
}

const UnicodeString & User::getUsername() const {
	return username;
}

void User::setUsername(const UnicodeString &_username) {
	username = _username;
}

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

const UserType& User::getUserType() const {
	   return userType;
}

void User::setUserType(const UserType &_userType) {
	userType = _userType;
}


