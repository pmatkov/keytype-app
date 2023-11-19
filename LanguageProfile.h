//---------------------------------------------------------------------------

#ifndef LanguageProfileH
#define LanguageProfileH
//---------------------------------------------------------------------------
#include<vcl.h>

class LanguageProfile
{
	private:
		UnicodeString languageName;
		UnicodeString languageCode;
		UnicodeString alphabet;

		// vanjska dat
		//static enum allowedLanguages {EN, HR, DE, FR};

	public:
		LanguageProfile();
		LanguageProfile(UnicodeString _languageName, UnicodeString _languageCode, UnicodeString _alphabet);
        LanguageProfile(UnicodeString _languageName, UnicodeString _languageCode);
		//std::vector<std::string>& getAllowedLanguages() const;



};
#endif
