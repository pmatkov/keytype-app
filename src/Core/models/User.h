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
    	UnicodeString username;
        UnicodeString token;

		UserType userType = Guest;

	public:

		User();
        User(const UnicodeString &_username, const UnicodeString &_token);

        const UnicodeString &getUsername() const;
		void setUsername(const UnicodeString &_username);

        const UnicodeString &getToken() const;
		void setToken(const UnicodeString &_token);

		const UserType& getUserType() const;
		void setUserType(const UserType &_userType);

};

#endif
