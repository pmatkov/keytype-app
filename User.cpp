//---------------------------------------------------------------------------

#pragma hdrstop

#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

User::User() {
	name = "guest";
	surname = "guest";
}

User::User(std::string _name, std::string _surname) : name(_name), surname(_surname) {}

const std::string User::getName() const {
	return name;
}
const std::string User::getSurname() const {
	return surname;
}
