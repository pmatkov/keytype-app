//---------------------------------------------------------------------------

#ifndef DcWordH
#define DcWordH

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

class DcWord {

	private:
		UnicodeString word;
		WordCategory category;
		UnicodeString definition;
		std::vector<UnicodeString> synonyms;

		static std::vector<UnicodeString> enumStrings;

	public:
    	DcWord();
		DcWord(UnicodeString _word, WordCategory _category, UnicodeString _definition, std::vector<UnicodeString> _synonyms);
		const UnicodeString& getWord() const;
		const WordCategory& getWordCategory() const;
		const UnicodeString& getDefinition() const;
		const std::vector<UnicodeString>& getSynonyms() const;
		UnicodeString getSynonymsAsString() const;

		static WordCategory stringToWordCategory(const UnicodeString &word);
        static UnicodeString wordCategoryToString(WordCategory category);
        static std::vector<UnicodeString> getWordCategoriesAsStrings();

};
//---------------------------------------------------------------------------
#endif
