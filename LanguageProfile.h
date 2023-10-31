//---------------------------------------------------------------------------

#ifndef LanguageProfileH
#define LanguageProfileH
//---------------------------------------------------------------------------
#include <vcl.h>
#include<string>
#include<vector>

class LanguageProfile
{
	private:
		std::string languageName;
		std::string languageCode;
		UnicodeString alphabet;

		// vanjska dat
		//static enum allowedLanguages {EN, HR, DE, FR};

	public:
		LanguageProfile(std::string _languageName, std::string _languageCode, UnicodeString _alphabet);
		//std::vector<std::string>& getAllowedLanguages() const;



};
#endif
