//---------------------------------------------------------------------------

#ifndef DictionaryEntryH
#define DictionaryEntryH

#include <vcl.h>
#include <vector>

enum class WordCategory {
	Noun,
	Verb,
	Adverb,
	Adjective,
	Pronoun,
	Count,
	Unknown
};


class DictionaryEntry {

    private:
        UnicodeString word;
        WordCategory category;
        UnicodeString definition;
        std::vector<UnicodeString> synonyms;

        static std::vector<UnicodeString> enumStrings;

    public:
        DictionaryEntry();
        DictionaryEntry(UnicodeString _word, WordCategory _category, UnicodeString _definition, std::vector<UnicodeString> _synonyms);

        const UnicodeString& getWord() const;
        const WordCategory& getWordCategory() const;
        const UnicodeString& getDefinition() const;
        const std::vector<UnicodeString>& getSynonyms() const;
        UnicodeString getSynonymsAsString() const;

        static std::vector<UnicodeString>& getEnumStrings();

        bool operator==(const DictionaryEntry& other) const;


};

//---------------------------------------------------------------------------
#endif
