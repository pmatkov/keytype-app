//---------------------------------------------------------------------------

#ifndef UserH
#define UserH
//---------------------------------------------------------------------------

#include <vcl.h>

#include "UserStatistics.h"

enum UserType {
	Registered,
	Guest
};

class User {

	private:
		UnicodeString name;
		UnicodeString surname;
		int age;
		UnicodeString username;
		UnicodeString email;
		UserStatistics userStats;

		UserType userType;
		bool isLoggedIn;

	public:

		User();
		User(const UnicodeString &_username, bool _isLoggedIn);
		User(const UnicodeString &_name, const UnicodeString &_surname, int _age, const UnicodeString &_username, const UnicodeString &_email);

		const UnicodeString & getName() const;
		void setName(const UnicodeString &_name);
		const UnicodeString & getSurname() const;
		void setSurname(const UnicodeString &_surname);
		int getAge() const;
		void setAge(int _age);
		const UnicodeString & getUsername() const;
		void setUsername(const UnicodeString &_username);

		const UserType& getUserType() const;
		void setUserType(const UserType &_userType);
		bool getIsLoggedIn() const;
		void setIsLoggedIn(bool _isLoggedIn);

};

#endif
