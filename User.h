//---------------------------------------------------------------------------

#ifndef UserH
#define UserH
//---------------------------------------------------------------------------


#include <string>

class User {

	private:
		std::string name;
		std::string surname;
	public:
        User();
		User(std::string _name, std::string _surname);

		const std::string getName() const;
		const std::string getSurname() const;
};

#endif
