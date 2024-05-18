//---------------------------------------------------------------------------

#pragma hdrstop

#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


User::User() {
	userType = Guest;
}

User::User(const UnicodeString &_username) : username(_username) {
	userType = Registered;
};

const UnicodeString &User::getUsername() const {
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


