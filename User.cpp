//---------------------------------------------------------------------------

#pragma hdrstop

#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


User::User() {
	userType = Guest;
}

User::User(const UnicodeString &_username, const UnicodeString &_password) : username(_username), password(_password)  {
	userType = Registered;
};

User::User(const UnicodeString &_id, const UnicodeString &_username,  const UnicodeString &_password, const UnicodeString &_name, const UnicodeString &_surname, int _age,  const UnicodeString &_email) :
id (_id), username(_username), password(_password), name(_name), surname(_surname), age(_age), email(_email) {
	userType = Registered;
}

const UnicodeString &User::getUsername() const {
	return username;
}

void User::setUsername(const UnicodeString &_username) {
	username = _username;
}

const UnicodeString &User::getPassword() const {
   return password;
}

void User::setPassword(const UnicodeString &_password) {
    password = _password;
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

void User::setSurname(const UnicodeString &_surname) {
	surname = _surname;
}

int User::getAge() const {
	return age;
}

void User::setAge(int _age) {
	age = _age;
}

const UnicodeString& User::getEmail() {
   	return email;
}

void User::setEmail(const UnicodeString &_email) {
	email = _email;
}

const UserType& User::getUserType() const {
	   return userType;
}

void User::setUserType(const UserType &_userType) {
	userType = _userType;
}


