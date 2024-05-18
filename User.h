//---------------------------------------------------------------------------

#ifndef UserH
#define UserH
//---------------------------------------------------------------------------

#include <vcl.h>

enum UserType {
	Registered,
	Guest
};

class User {

	private:
    	UnicodeString username = "";

		UserType userType = Guest;

	public:

		User();
        User(const UnicodeString &_username);

        const UnicodeString & getUsername() const;
		void setUsername(const UnicodeString &_username);

		const UserType& getUserType() const;
		void setUserType(const UserType &_userType);

};

#endif
