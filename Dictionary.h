//---------------------------------------------------------------------------

#ifndef DictionaryH
#define DictionaryH

#include<vector>
#include<vcl.h>
#include "LanguageProfile.h"
#include "WordInfo.h"
//---------------------------------------------------------------------------

class Dictionary {
	private:
		std::vector<WordInfo> words;
		LanguageProfile language;
		int wordCount;

	public:

};
#endif
