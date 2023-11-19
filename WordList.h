//---------------------------------------------------------------------------

#ifndef WordListH
#define WordListH

#include <vector>
#include <vcl.h>
#include "LanguageProfile.h"
#include "WordInfo.h"

class WordList {
	private:
		UnicodeString listName;
		UnicodeString description;
		LanguageProfile language;
		std::vector<UnicodeString> wordList;

	public:
		WordList(UnicodeString _listName, std::vector<UnicodeString> _wordList);
        const UnicodeString& getWordListName() const;
		const std::vector<UnicodeString>& getWordList() const;
		void setWordList(const std::vector<UnicodeString>& _wordList);
};

//---------------------------------------------------------------------------
#endif
