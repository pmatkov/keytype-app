//---------------------------------------------------------------------------

#ifndef WordListH
#define WordListH

#include <vector>
#include <optional>
#include <vcl.h>

#include "LanguageProfile.h"

class WordList {
	private:
    	std::vector<UnicodeString> wordList;
		UnicodeString listName;
		UnicodeString description;
		LanguageProfile language;

	public:
		WordList(UnicodeString _listName, std::vector<UnicodeString> _wordList);
        const UnicodeString& getWordListName() const;
		const std::vector<UnicodeString>& getWordList() const;
		void setWordList(const std::vector<UnicodeString>& _wordList);

        static std::optional<std::vector<UnicodeString>> parseTextToWordList(const UnicodeString &path);
};

//---------------------------------------------------------------------------
#endif
