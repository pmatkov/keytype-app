//---------------------------------------------------------------------------

#ifndef WordInfoH
#define WordInfoH

#include <vcl.h>
#include <vector>

enum WordType {
	Noun,
	Verb,
	Adverb,
	Adjective,
	Pronoun,
	Conjunction,
	Preposition
};

class WordInfo {

	private:
		UnicodeString word;
		WordType wordType;
		UnicodeString definition;
		std::vector<UnicodeString> synonyms;
		std::vector<UnicodeString> antonyms;
		std::vector<UnicodeString> examples;

	public:
		const UnicodeString& getWord() const;
		const WordType& getWordType() const;

};
//---------------------------------------------------------------------------
#endif
