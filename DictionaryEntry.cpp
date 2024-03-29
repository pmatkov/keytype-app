//---------------------------------------------------------------------------

#pragma hdrstop

#include "DictionaryEntry.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

DictionaryEntry::DictionaryEntry(){}

DictionaryEntry::DictionaryEntry(UnicodeString _word, WordCategory _category, UnicodeString _definition, std::vector<UnicodeString> _synonyms)
        : word(_word), category(_category), definition(_definition), synonyms(_synonyms) {}

const UnicodeString& DictionaryEntry::getWord() const {
    return word;
}

const WordCategory& DictionaryEntry::getWordCategory() const {
    return category;
}

const UnicodeString& DictionaryEntry::getDefinition() const {
    return definition;
}

const std::vector<UnicodeString>& DictionaryEntry::getSynonyms() const {
    return synonyms;
}

UnicodeString DictionaryEntry::getSynonymsAsString() const {

    UnicodeString synonymsString = "";

    for (const UnicodeString &synonym : synonyms) {
         synonymsString += synonym + ", ";
    }

    synonymsString = synonymsString.Delete(synonymsString.Length()-1, 2);

    return synonymsString;
}

std::vector<UnicodeString>& DictionaryEntry::getEnumStrings() {
    return enumStrings;
}

std::vector<UnicodeString> DictionaryEntry::enumStrings = {"noun", "verb", "adverb", "adjective", "pronoun"};

bool DictionaryEntry::operator==(const DictionaryEntry& other) const {

     if (word == other.word && category == other.category && definition == other.definition && getSynonymsAsString() == other.getSynonymsAsString()) {
            return true;
     }
     else {
        return false;
     }
}
