//---------------------------------------------------------------------------

#pragma hdrstop

#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

User::User() {}

User::User(const UnicodeString &_username, const UnicodeString &_token) : username(_username), token(_token) {

    if (username == "guest") {
    	userType = Guest;
    }
    else {
		userType = Registered;
    }
};

const UnicodeString &User::getUsername() const {
	return username;
}

void User::setUsername(const UnicodeString &_username) {
	username = _username;
}

const UnicodeString &User::getToken() const {
   return token;
}

void User::setToken(const UnicodeString &_token) {
    token = _token;
}

const UserType& User::getUserType() const {
	   return userType;
}

void User::setUserType(const UserType &_userType) {
	userType = _userType;
}


