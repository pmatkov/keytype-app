//---------------------------------------------------------------------------

#ifndef LanguageProfileH
#define LanguageProfileH
//---------------------------------------------------------------------------
#include <vcl.h>
#include<vector>

class LanguageProfile
{
	private:
		UnicodeString languageName;
		UnicodeString languageCode;
		UnicodeString alphabet;

		// vanjska dat
		//static enum allowedLanguages {EN, HR, DE, FR};

	public:
		LanguageProfile(UnicodeString _languageName, UnicodeString _languageCode, UnicodeString _alphabet);
		//std::vector<std::string>& getAllowedLanguages() const;



};
#endif
