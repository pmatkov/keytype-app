//---------------------------------------------------------------------------

#pragma hdrstop

#include "LanguageProfile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

LanguageProfile::LanguageProfile(std::string _languageName, std::string _languageCode, UnicodeString _alphabet) : languageName (_languageName), languageCode(_languageCode), alphabet(_alphabet) {}

//	if (std::find(allowedLanguages.begin(), allowedLanguages.end(), _languageCode)) {
//
//	} else {
//
//	}

//std::vector<std::string> const& LanguageProfile::getAllowedLanguages() const {
//
//	return allowedLanguages;
//}

