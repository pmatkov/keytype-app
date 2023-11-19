//---------------------------------------------------------------------------

#pragma hdrstop

#include "WordInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

WordInfo::WordInfo(){}
WordInfo::WordInfo(UnicodeString _word, WordCategory _category, UnicodeString _definition, std::vector<UnicodeString> _synonyms)
		: word(_word), category(_category), definition(_definition), synonyms(_synonyms) {}

const UnicodeString& WordInfo::getWord() const {
	   return word;
}

const WordCategory& WordInfo::getWordCategory() const {
	   return category;
}

const UnicodeString& WordInfo::getDefinition() const {
	   return definition;
}

const std::vector<UnicodeString>& WordInfo::getSynonyms() const {
      return synonyms;
}

UnicodeString WordInfo::getSynonymsAsString() const {

	UnicodeString synonymsString = "";

	for (const UnicodeString &synonym : synonyms) {
		 synonymsString += synonym + ", ";
	}

	synonymsString = synonymsString.Delete(synonymsString.Length()-1, 2);

	return synonymsString;
}


WordCategory WordInfo::stringToWordCategory(const UnicodeString &word) {

	std::vector<UnicodeString>::iterator it = std::find(enumStrings.begin(), enumStrings.end(), word);

	if (it != enumStrings.end()) {
		 return static_cast<WordCategory> (it - enumStrings.begin());
	}
	else
		return Unknown;
}

UnicodeString WordInfo::wordCategoryToString(WordCategory category) {

	if (static_cast<int>(category) < enumStrings.size()	) {
		return enumStrings[static_cast<int>(category)];
	}
	else
		return "unkown";
}

 std::vector<UnicodeString> WordInfo::enumStrings = {"noun", "verb", "adverb", "adjective", "pronoun"};
