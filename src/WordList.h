//---------------------------------------------------------------------------

#ifndef WordListH
#define WordListH

#include <vector>
#include <optional>
#include <vcl.h>


class WordList {

	private:
    	std::vector<UnicodeString> words;
		UnicodeString name;

	public:
   		WordList();
		WordList(std::vector<UnicodeString> _words, UnicodeString _name);

        const std::vector<UnicodeString>& getWords() const;
		void setWords(const std::vector<UnicodeString>& _words);
        const UnicodeString& getName() const;

        void parseTextToWordList(const UnicodeString &path);
};

//---------------------------------------------------------------------------
#endif
