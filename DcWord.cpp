//---------------------------------------------------------------------------

#pragma hdrstop

#include "DcWord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

DcWord::DcWord(){}
DcWord::DcWord(UnicodeString _word, WordCategory _category, UnicodeString _definition, std::vector<UnicodeString> _synonyms)
		: word(_word), category(_category), definition(_definition), synonyms(_synonyms) {}

const UnicodeString& DcWord::getWord() const {
	   return word;
}

const WordCategory& DcWord::getWordCategory() const {
	   return category;
}

const UnicodeString& DcWord::getDefinition() const {
	   return definition;
}

const std::vector<UnicodeString>& DcWord::getSynonyms() const {
      return synonyms;
}

UnicodeString DcWord::getSynonymsAsString() const {

	UnicodeString synonymsString = "";

	for (const UnicodeString &synonym : synonyms) {
		 synonymsString += synonym + ", ";
	}

	synonymsString = synonymsString.Delete(synonymsString.Length()-1, 2);

	return synonymsString;
}


WordCategory DcWord::stringToWordCategory(const UnicodeString &word) {

	std::vector<UnicodeString>::iterator it = std::find(enumStrings.begin(), enumStrings.end(), word);

	if (it != enumStrings.end()) {
		 return static_cast<WordCategory> (it - enumStrings.begin());
	}
	else
		return Unknown;
}

UnicodeString DcWord::wordCategoryToString(WordCategory category) {

	if (static_cast<int>(category) < enumStrings.size()	) {
		return enumStrings[static_cast<int>(category)];
	}
	else
		return "unkown";
}

std::vector<UnicodeString> DcWord::getWordCategoriesAsStrings() {

	std::vector<UnicodeString> categories;

	int count = static_cast<int> (WordCategory::Count);

    for (int i = 0; i < count; i++) {
    	categories.push_back(wordCategoryToString(static_cast<WordCategory>(i)));
    }

    return categories;
}

std::vector<UnicodeString> DcWord::enumStrings = {"noun", "verb", "adverb", "adjective", "pronoun"};
