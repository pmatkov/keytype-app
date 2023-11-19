//---------------------------------------------------------------------------

#ifndef WordInfoH
#define WordInfoH

#include <vcl.h>
#include <vector>

enum WordCategory {
	Noun,
	Verb,
	Adverb,
	Adjective,
	Pronoun,
	Count,
	Unknown
};

class WordInfo {

	private:
		UnicodeString word;
		WordCategory category;
		UnicodeString definition;
		std::vector<UnicodeString> synonyms;

		static std::vector<UnicodeString> enumStrings;

	public:
    	WordInfo();
		WordInfo(UnicodeString _word, WordCategory _category, UnicodeString _definition, std::vector<UnicodeString> _synonyms);
		const UnicodeString& getWord() const;
		const WordCategory& getWordCategory() const;
		const UnicodeString& getDefinition() const;
		const std::vector<UnicodeString>& getSynonyms() const;
		UnicodeString getSynonymsAsString() const;

		static WordCategory stringToWordCategory(const UnicodeString &word);
        static UnicodeString wordCategoryToString(WordCategory category);

};
//---------------------------------------------------------------------------
#endif
