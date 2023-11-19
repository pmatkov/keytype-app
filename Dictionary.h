//---------------------------------------------------------------------------

#ifndef DictionaryH
#define DictionaryH


#include<vector>
#include <optional>
#include<vcl.h>
#include<map>

#include "LanguageProfile.h"
#include "WordInfo.h"

//---------------------------------------------------------------------------

class Dictionary {

	private:
		std::map<UnicodeString, WordInfo> words;
		LanguageProfile language;
		int wordCount;

	public:
		const std::map<UnicodeString, WordInfo>& getWords() const;
		std::optional<WordInfo> getWordInfo(const UnicodeString &key);
		void setWordInfo(UnicodeString key, WordInfo value);
        void deleteWordInfo(const UnicodeString &key);
		void parseJsontoWordInfo(const UnicodeString &relPath);

		static std::optional<UnicodeString> generateJsonFromWordInfo(const std::map<UnicodeString, WordInfo> &words);
};
#endif
