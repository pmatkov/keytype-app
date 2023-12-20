//---------------------------------------------------------------------------

#pragma hdrstop

#include <algorithm>
#include <System.JSON.hpp>

#include "Dictionary.h"
#include "FileUtils.h"
#include "TextUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

const std::map<UnicodeString, DcWord>& Dictionary::getDictionary() const {

    return dictionary;
}

std::optional<DcWord> Dictionary::getWord(const UnicodeString &key) {

   std::map<UnicodeString, DcWord>::iterator it = dictionary.find(key);

	if (it != dictionary.end()) {
		return it->second;
	} else {
		return std::nullopt;
	}

}

void Dictionary::setWord(UnicodeString key, DcWord value) {
	dictionary[key] = value;
}

void Dictionary::deleteWord(const UnicodeString &key) {

	std::map<UnicodeString, DcWord>::iterator it = dictionary.find(key);

	if (it != dictionary.end()) {
		dictionary.erase(it);
	}
}


void Dictionary::parseJsonToDictionary(const UnicodeString &path) {

	TJSONObject *mainObject, *wordObject;
	TJSONArray *dictionaryObject, *synonymsObject;

	try {

		mainObject = (TJSONObject*) FileUtils::readFromJsonFile(path);
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

							dictionary[word] = DcWord(word, DcWord::stringToWordCategory(category), definition, synonyms);

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


std::optional<UnicodeString> Dictionary::generateJsonFromDictionary(const std::map<UnicodeString, DcWord> &dictionary) {

	UnicodeString result = "";

	if (dictionary.size() > 0) {

		TJSONObject *mainObject, *wordObject;
		TJSONArray *dictionaryObject, *synonymsObject;

		try {
			mainObject = new TJSONObject();

			try
			{
				dictionaryObject = new TJSONArray();

				mainObject->AddPair("dictionary", dictionaryObject);

				for (const std::pair<const UnicodeString, DcWord>& keyValue : dictionary) {

					UnicodeString word = keyValue.second.getWord();
					UnicodeString category = DcWord::wordCategoryToString(keyValue.second.getWordCategory());
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
	if (!result.IsEmpty()) {
		 return result;
	}
	else
		return std::nullopt;

}


