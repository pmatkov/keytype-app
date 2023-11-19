//---------------------------------------------------------------------------

#pragma hdrstop

#include <algorithm>
#include <System.JSON.hpp>

#include "Dictionary.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "WordInfo.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)

const std::map<UnicodeString, WordInfo>& Dictionary::getWords() const {

    return words;
}

std::optional<WordInfo> Dictionary::getWordInfo(const UnicodeString &key) {

   std::map<UnicodeString, WordInfo>::iterator it = words.find(key);

	if (it != words.end()) {
		return it->second;
	} else {
		return std::nullopt;
	}

}

void Dictionary::setWordInfo(UnicodeString key, WordInfo value) {
	words[key] = value;
}

void Dictionary::deleteWordInfo(const UnicodeString &key) {

	std::map<UnicodeString, WordInfo>::iterator it = words.find(key);

	if (it != words.end()) {
		words.erase(it);
	}
}


void Dictionary::parseJsontoWordInfo(const UnicodeString &relPath) {

	TJSONObject *mainObject, *wordObject;
	TJSONArray *dictionaryObject, *synonymsObject;

	try {

		mainObject = (TJSONObject*) FileUtils::readJsonFromFile(relPath);
		try {

			if (mainObject) {

				dictionaryObject = static_cast<TJSONArray*> (TJSONObject::ParseJSONValue(mainObject->Values["dictionary"]->ToString()));

				if (dictionaryObject) {

					for (int i = 0; i < dictionaryObject->Count; i++) {

						wordObject = static_cast<TJSONObject*> (dictionaryObject->Items[i]);

						if (wordObject) {

							UnicodeString word, category, definition;
							std::vector<UnicodeString> synonyms;

							if (wordObject->Values["word"])
								word = TextUtils::trimCharacters(wordObject->Values["word"]->ToString(), L'\"');
							if (wordObject->Values["category"])
								category = TextUtils::trimCharacters(wordObject->Values["category"]->ToString(), L'\"');
							if (wordObject->Values["definition"])
								definition = TextUtils::trimCharacters(wordObject->Values["definition"]->ToString(), L'\"');

							synonymsObject = static_cast<TJSONArray*> (wordObject->Values["synonyms"]);

							if (synonymsObject) {

								for (int j = 0; j < synonymsObject->Count; j++)   {
									synonyms.push_back(TextUtils::trimCharacters(synonymsObject->Items[j]->ToString(), L'\"'));
								}
							}

							words[word] = WordInfo(word, WordInfo::stringToWordCategory(category), definition, synonyms);

						}
					}
				}
			}
		}

		__finally {
			mainObject->Free();
		}

	} catch (const Exception &ex) {
		ShowMessage("Unable to parse JSON");
	}

}


std::optional<UnicodeString> Dictionary::generateJsonFromWordInfo(const std::map<UnicodeString, WordInfo> &words) {

	UnicodeString result = "";

	if (words.size() > 0) {

		TJSONObject *mainObject, *wordObject;
		TJSONArray *dictionaryObject, *synonymsObject;

		try {
			mainObject = new TJSONObject();

			try
			{
				dictionaryObject = new TJSONArray();

				mainObject->AddPair("dictionary", dictionaryObject);

				for (const std::pair<const UnicodeString, WordInfo>& keyValue : words) {

					UnicodeString word = keyValue.second.getWord();
					UnicodeString category = WordInfo::wordCategoryToString(keyValue.second.getWordCategory());
					UnicodeString definition = keyValue.second.getDefinition();

					wordObject = new TJSONObject();
					synonymsObject = new TJSONArray();

					for (const UnicodeString &string : keyValue.second.getSynonyms()) {
						synonymsObject->Add(string);
					}

					wordObject->AddPair(new TJSONPair("word", word));
					wordObject->AddPair(new TJSONPair("category", category));
					wordObject->AddPair(new TJSONPair("definition", definition));
					wordObject->AddPair(new TJSONPair("synonyms", synonymsObject));

					dictionaryObject->AddElement(wordObject);

				}

				result += TextUtils::formatJson(mainObject->ToString());
				}
				__finally {
					mainObject->Free();
				}
		} catch (const Exception &ex) {
			ShowMessage("Unable to generate JSON");
		}

	}
	if (result.Length()) {
		 return result;
	}
	else
		return std::nullopt;

}


