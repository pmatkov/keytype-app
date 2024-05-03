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
        UnicodeString id = "";
    	UnicodeString username = "";
        UnicodeString password = "";
		UnicodeString name = "";
		UnicodeString surname = "";
        UnicodeString email = "";
		int age = 0;

		UserStatistics userStats;
		UserType userType = Guest;

	public:

		User();
        User(const UnicodeString &_username, const UnicodeString &_password);
		User(const UnicodeString &_id, const UnicodeString &_username, const UnicodeString &_password, const UnicodeString &_name, const UnicodeString &_surname, int _age,  const UnicodeString &_email);

        const UnicodeString & getUsername() const;
		void setUsername(const UnicodeString &_username);

        const UnicodeString &getPassword() const;
		void setPassword(const UnicodeString &_password);

		const UnicodeString & getName() const;
		void setName(const UnicodeString &_name);

		const UnicodeString & getSurname() const;
		void setSurname(const UnicodeString &_surname);

		int getAge() const;
		void setAge(int _age);

        const UnicodeString & getEmail();
       	void setEmail(const UnicodeString &_email);

		const UserType& getUserType() const;
		void setUserType(const UserType &_userType);

};

#endif
