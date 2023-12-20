//---------------------------------------------------------------------------

#pragma hdrstop

#include "Word.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Word::Word(){}
Word::Word(UnicodeString _word, WordCategory _category, UnicodeString _definition, std::vector<UnicodeString> _synonyms)
		: word(_word), category(_category), definition(_definition), synonyms(_synonyms) {}

const UnicodeString& Word::getWord() const {
	   return word;
}

const WordCategory& Word::getWordCategory() const {
	   return category;
}

const UnicodeString& Word::getDefinition() const {
	   return definition;
}

const std::vector<UnicodeString>& Word::getSynonyms() const {
      return synonyms;
}

UnicodeString Word::getSynonymsAsString() const {

	UnicodeString synonymsString = "";

	for (const UnicodeString &synonym : synonyms) {
		 synonymsString += synonym + ", ";
	}

	synonymsString = synonymsString.Delete(synonymsString.Length()-1, 2);

	return synonymsString;
}


WordCategory Word::stringToWordCategory(const UnicodeString &word) {

	std::vector<UnicodeString>::iterator it = std::find(enumStrings.begin(), enumStrings.end(), word);

	if (it != enumStrings.end()) {
		 return static_cast<WordCategory> (it - enumStrings.begin());
	}
	else
		return Unknown;
}

UnicodeString Word::wordCategoryToString(WordCategory category) {

	if (static_cast<int>(category) < enumStrings.size()	) {
		return enumStrings[static_cast<int>(category)];
	}
	else
		return "unkown";
}

std::vector<UnicodeString> Word::getWordCategoriesAsStrings() {

	std::vector<UnicodeString> categories;

	int count = static_cast<int> (WordCategory::Count);

    for (int i = 0; i < count; i++) {
    	categories.push_back(wordCategoryToString(static_cast<WordCategory>(i)));
    }

    return categories;
}

std::vector<UnicodeString> Word::enumStrings = {"noun", "verb", "adverb", "adjective", "pronoun"};
