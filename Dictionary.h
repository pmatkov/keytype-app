//---------------------------------------------------------------------------

#ifndef DictionaryH
#define DictionaryH


#include<vector>
#include <optional>
#include<vcl.h>
#include<map>

#include "LanguageProfile.h"
#include "DcWord.h"

//---------------------------------------------------------------------------

class Dictionary {

	private:
		std::map<UnicodeString, DcWord> dictionary;
		LanguageProfile language;
		int wordCount;

	public:
		const std::map<UnicodeString, DcWord>& getDictionary() const;
		std::optional<DcWord> getWord(const UnicodeString &key);
		void setWord(UnicodeString key, DcWord value);
        void deleteWord(const UnicodeString &key);

		void parseJsonToDictionary(const UnicodeString &path);
		static std::optional<UnicodeString> generateJsonFromDictionary(const std::map<UnicodeString, DcWord> &dictionary);
};
#endif
