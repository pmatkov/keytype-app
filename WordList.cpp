//---------------------------------------------------------------------------

#pragma hdrstop

#include "WordList.h"
#include "TextUtils.h"
#include "FileUtils.h"
#include "Logger.h"
#include "EFileNotFoundException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

WordList::WordList(UnicodeString _listName, std::vector<UnicodeString> _wordList) : listName (_listName), wordList(_wordList) {}

const UnicodeString& WordList::getWordListName() const {
	return listName;
}

const std::vector<UnicodeString>& WordList::getWordList() const {
	return wordList;
}

void WordList::setWordList(const std::vector<UnicodeString>& _wordList) {
    wordList = _wordList;
}

std::optional<std::vector<UnicodeString>> WordList::parseTextToWordList(const UnicodeString &path) {

	std::optional<UnicodeString> wordlist;

    try {
    	wordlist = FileUtils::readFromTextFile(path);
    } catch (CustomExceptions::EFileNotFoundException &ex) {
        LOGGER(LogLevel::Fatal, ex.getMessage());
    }

    if (wordlist.has_value()) {

        std::vector<UnicodeString> wlContents;

        if (TextUtils::countWords(*wordlist) > 1) {

            std::vector<UnicodeString> words = TextUtils::splitTextIntoWords(*wordlist);
            wlContents.insert(wlContents.end(), words.begin(), words.end());
        }
        else {
            wlContents.push_back(*wordlist);
        }

        return wlContents;

    }

    return std::nullopt;
}



