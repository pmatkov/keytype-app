//---------------------------------------------------------------------------

#pragma hdrstop

#include <algorithm>
#include <System.JSON.hpp>

#include "Dictionary.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "EnumUtils.h"
#include "UIUtils.h"
#include "Logger.h"
#include "EFileNotFoundException.h"
#include "EDirNotFoundException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

Dictionary::Dictionary(IDisplay &_uiDisplay) : uiDisplay(_uiDisplay) {

     std::optional<std::vector<UnicodeString>> fileNames = findDictionaryFiles();
     if (fileNames.has_value()) {

     	uiDisplay.setItemsMultiItemControl("DictionaryFiles", *fileNames, 0);
        setDictionary((*fileNames)[0]);
    }

    uiDisplay.setItemsMultiItemControl("Category", DictionaryEntry::getEnumStrings(), -1);
    uiDisplay.setItemSingleItemControl("FileDialog", "Data");

}

const std::map<UnicodeString, DictionaryEntry>& Dictionary::getDictionary() const {

    return dictionary;
}

std::vector<UnicodeString> Dictionary::getDictionaryKeys() {

	std::vector<UnicodeString> keys;
  	for (const std::pair<const UnicodeString, DictionaryEntry>& item : dictionary) {
    	keys.push_back(item.first);
  	}
  	return keys;
}

std::vector<DictionaryEntry> Dictionary::getDictionaryValues() {

	std::vector<DictionaryEntry> values;
  	for (const std::pair<const UnicodeString, DictionaryEntry>& item : dictionary) {
    	values.push_back(item.second);
  	}
  	return values;
}

std::vector<UnicodeString> Dictionary::getDictionaryValuesAsStrings() {

   std::vector<DictionaryEntry> values = getDictionaryValues();
   std::vector<UnicodeString> valuesStr;

   for (const DictionaryEntry &value : values) {
    	valuesStr.insert(valuesStr.end(), {value.getWord(), EnumUtils::enumToString<WordCategory>(DictionaryEntry::getEnumStrings(), \
        value.getWordCategory()), value.getDefinition(), value.getSynonymsAsString()});
  	}

    return valuesStr;
}


std::optional<DictionaryEntry> Dictionary::internalGetDictionaryEntry(const UnicodeString &key) {

   std::map<UnicodeString, DictionaryEntry>::iterator it = dictionary.find(key);

	if (it != dictionary.end()) {
		return it->second;
	} else {
		return std::nullopt;
	}

}

void Dictionary::internalSetDictionaryEntry(UnicodeString key, DictionaryEntry value) {
	dictionary[key] = value;
}

void Dictionary::internalDeleteDictionaryEntry(const UnicodeString &key) {

	std::map<UnicodeString, DictionaryEntry>::iterator it = dictionary.find(key);

	if (it != dictionary.end()) {
		dictionary.erase(it);
	}
}

void Dictionary::parseJsonToDictionary(const UnicodeString &path) {

	TJSONObject *mainObject, *wordObject;
	TJSONArray *dictionaryObject, *synonymsObject;

	try {
        std::optional<UnicodeString> string = FileUtils::readFromTextFile(path);

        if (string.has_value()) {

        	dictionary.clear();
        	mainObject = (TJSONObject*) TextUtils::convertToJSONObject(*string);

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

                                dictionary[word] = DictionaryEntry(word, EnumUtils::stringToEnum<WordCategory>(DictionaryEntry::getEnumStrings(), category), definition, synonyms);

                            }
                        }
                    }
                }
            }

            __finally {
                mainObject->Free();
            }
        }

	}
    catch (CustomExceptions::EFileNotFoundException &ex) {
        LOGGER(LogLevel::Fatal, ex.getMessage());
    }
    catch (const Exception &ex) {
		ShowMessage("Unable to parse JSON");
        LOGGER(LogLevel::Error, "Error parsing JSON format");
	}

}


std::optional<UnicodeString> Dictionary::generateJsonFromDictionary(const std::map<UnicodeString, DictionaryEntry> &dictionary) {

	UnicodeString jsonString = "";

		TJSONObject *mainObject, *dictionaryEntryObject;
		TJSONArray *dictionaryArray, *synonymsArray;

		try {

            mainObject = new TJSONObject();
			try {
				dictionaryArray = new TJSONArray();

				mainObject->AddPair("dictionary", dictionaryArray);

				for (const std::pair<const UnicodeString, DictionaryEntry>& item : dictionary) {

					UnicodeString word = item.second.getWord();
					UnicodeString category = EnumUtils::enumToString<WordCategory>(DictionaryEntry::getEnumStrings(), item.second.getWordCategory());

					UnicodeString definition = item.second.getDefinition();

					dictionaryEntryObject = new TJSONObject();
					synonymsArray = new TJSONArray();

					for (const UnicodeString &string : item.second.getSynonyms()) {
						synonymsArray->Add(string);
					}

					dictionaryEntryObject->AddPair(new TJSONPair("word", word));
					dictionaryEntryObject->AddPair(new TJSONPair("category", category));
					dictionaryEntryObject->AddPair(new TJSONPair("definition", definition));
					dictionaryEntryObject->AddPair(new TJSONPair("synonyms", synonymsArray));

					dictionaryArray->AddElement(dictionaryEntryObject);
				}

				jsonString += TextUtils::formatJson(mainObject->ToString());
				}
            __finally {
                mainObject->Free();
            }
		} catch (const Exception &ex) {
			ShowMessage("Unable to generate JSON");
            LOGGER(LogLevel::Error, "Error converting to JSON");
		}


	if (!jsonString.IsEmpty()) {
		 return jsonString;
	}
	else {
		return std::nullopt;
    }
}


std::optional<UnicodeString> Dictionary::generateJsonFromWordList(const std::vector<UnicodeString> &wordList) {

	UnicodeString jsonString = "";

    TJSONObject *mainObject, *dictionaryEntryObject;
    TJSONArray *dictionaryArray, *synonymsArray;

    try {

        mainObject = new TJSONObject();
        try {
            dictionaryArray = new TJSONArray();

            mainObject->AddPair("dictionary", dictionaryArray);

            for (const UnicodeString& word: wordList) {

                if (!word.Length()) {
                    continue;
                }

                dictionaryEntryObject = new TJSONObject();
            	synonymsArray = new TJSONArray();
                synonymsArray->Add(UnicodeString(L""));

                dictionaryEntryObject->AddPair(new TJSONPair("word", word));
       			dictionaryEntryObject->AddPair(new TJSONPair("category", UnicodeString(L"")));
				dictionaryEntryObject->AddPair(new TJSONPair("definition", UnicodeString(L"")));
                dictionaryEntryObject->AddPair(new TJSONPair("synonyms", synonymsArray));

                dictionaryArray->AddElement(dictionaryEntryObject);
            }

        jsonString += TextUtils::formatJson(mainObject->ToString());
    	}
        __finally {
        	mainObject->Free();
    	}

    } catch (const Exception &ex) {
        ShowMessage("Unable to generate JSON");
        LOGGER(LogLevel::Error, "Error converting to JSON");
    }

	if (!jsonString.IsEmpty()) {
		 return jsonString;
	}
	else {
		return std::nullopt;
    }

}

bool Dictionary::isInDictionary(const UnicodeString &word) {
     if (UIUtils::findItemIndex(getDictionaryKeys(), word) != -1) {
        return true;
     }
     else {
        return false;
     }
}

bool Dictionary::isEqualToDictionaryItem(const DictionaryEntry &dictionaryEntry) {

    for (const DictionaryEntry &value : getDictionaryValues()) {
      if (dictionaryEntry == value) {
          return true;
      }
    }
    return false;

}

void Dictionary::getDictionaryEntry(const UnicodeString &word) {

   	std::optional<DictionaryEntry> dictionaryEntry = internalGetDictionaryEntry(word);

    if (dictionaryEntry.has_value()) {

       	UnicodeString category = EnumUtils::enumToString<WordCategory>(DictionaryEntry::getEnumStrings(), (*dictionaryEntry).getWordCategory());

        if (category != "Unknown") {
        	uiDisplay.selectItemMultiItemControl("Category", category);
        }

        uiDisplay.setItemSingleItemControl("Word", word);
        uiDisplay.setItemSingleItemControl("Definition", (*dictionaryEntry).getDefinition());
        uiDisplay.setItemSingleItemControl("Synonyms", (*dictionaryEntry).getSynonymsAsString());
    }
}

void Dictionary::addDictionaryEntry(const UnicodeString &word, const DictionaryEntry &dictionaryEntry) {

    internalSetDictionaryEntry(word, dictionaryEntry);
	saveDictionaryToFile();
}

void Dictionary::deleteDictionaryEntry(const UnicodeString &word) {

	internalDeleteDictionaryEntry(word);
    saveDictionaryToFile();
}

std::optional<std::vector<UnicodeString>> Dictionary::findDictionaryFiles() {

	UnicodeString dirPath = FileUtils::createAbsolutePath("Data", false);
    std::optional<std::vector<UnicodeString>> fileNames;

    try {
    	fileNames = FileUtils::getFileNames(dirPath, "json");
    } catch (CustomExceptions::EDirNotFoundException &ex) {
        LOGGER(LogLevel::Fatal, ex.getMessage());
    }

    if (fileNames.has_value()) {
        return fileNames;
    }
    return std::nullopt;
}


void Dictionary::setDictionary(const UnicodeString &fileName) {

    parseJsonToDictionary(FileUtils::createAbsolutePath("Data", false) + fileName);
    uiDisplay.setItemsMultiItemControl("Dictionary", getDictionaryValuesAsStrings(), 4);

    dictionaryFileName = fileName;
}


void Dictionary::saveDictionaryToFile() {
	std::optional<UnicodeString> jsonString = generateJsonFromDictionary(dictionary);

    if (jsonString.has_value()) {

        FileUtils::saveToTextFile(FileUtils::createAbsolutePath("Data", false) + dictionaryFileName, std::vector<UnicodeString>{*jsonString});
        uiDisplay.setItemsMultiItemControl("Dictionary", getDictionaryValuesAsStrings(), 4);

    }

}

