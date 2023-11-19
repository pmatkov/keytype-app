//---------------------------------------------------------------------------



#include "LanguageProfile.h"
//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

LanguageProfile::LanguageProfile() {}
LanguageProfile::LanguageProfile(UnicodeString _languageName, UnicodeString _languageCode, UnicodeString _alphabet) : languageName (_languageName), languageCode(_languageCode), alphabet(_alphabet) {}
LanguageProfile::LanguageProfile(UnicodeString _languageName, UnicodeString _languageCode) : languageName (_languageName), languageCode(_languageCode){}
//	if (std::find(allowedLanguages.begin(), allowedLanguages.end(), _languageCode)) {
//
//	} else {
//
//	}

//std::vector<std::string> const& LanguageProfile::getAllowedLanguages() const {
//
//	return allowedLanguages;
//}

