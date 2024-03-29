//---------------------------------------------------------------------------

#ifndef DictionaryH
#define DictionaryH


#include <vector>
#include <optional>
#include <vcl.h>
#include <map>

#include "DictionaryEntry.h"
#include "IDisplay.h"

//---------------------------------------------------------------------------

class Dictionary {

	private:
        IDisplay &uiDisplay;
		std::map<UnicodeString, DictionaryEntry> dictionary;

        UnicodeString dictionaryFileName;

        std::optional<DictionaryEntry> internalGetDictionaryEntry(const UnicodeString &word);
        void internalSetDictionaryEntry(UnicodeString key, DictionaryEntry value);
        void internalDeleteDictionaryEntry(const UnicodeString &key);

	public:
        Dictionary(IDisplay &_uiDisplay);

		const std::map<UnicodeString, DictionaryEntry>& getDictionary() const;
        std::vector<UnicodeString> getDictionaryKeys();
        std::vector<DictionaryEntry> getDictionaryValues();
        std::vector<UnicodeString> getDictionaryValuesAsStrings();

		void parseJsonToDictionary(const UnicodeString &path);
		std::optional<UnicodeString> generateJsonFromDictionary(const std::map<UnicodeString, DictionaryEntry> &dictionary);
        static std::optional<UnicodeString> generateJsonFromWordList(const std::vector<UnicodeString> &wordList);

        bool isInDictionary(const UnicodeString &word);
        bool isEqualToDictionaryItem(const DictionaryEntry &dictionaryEntry);

        void getDictionaryEntry(const UnicodeString &word);
        void addDictionaryEntry(const UnicodeString &word, const DictionaryEntry &dictionaryEntry);
        void deleteDictionaryEntry(const UnicodeString &word);

        std::optional<std::vector<UnicodeString>> findDictionaryFiles();
        void setDictionary(const UnicodeString &path);
        void saveDictionaryToFile();
};
#endif
