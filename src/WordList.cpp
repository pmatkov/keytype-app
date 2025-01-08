//---------------------------------------------------------------------------

#pragma hdrstop

#include "WordList.h"
#include "TextUtils.h"
#include "FileUtils.h"
#include "Logger.h"
#include "EFileNotFoundException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

WordList::WordList() {}

WordList::WordList(std::vector<UnicodeString> _words, UnicodeString _name) : words(_words), name (_name) {}

const UnicodeString& WordList::getName() const {
	return name;
}

const std::vector<UnicodeString>& WordList::getWords() const {
	return words;
}

void WordList::setWords(const std::vector<UnicodeString>& _words) {
    words = _words;
}

void WordList::parseTextToWordList(const UnicodeString &path) {

	std::optional<UnicodeString> buffer;

    try {
    	buffer = FileUtils::readFromTextFile(path);
    } catch (CustomExceptions::EFileNotFoundException &ex) {
        LOGGER(LogLevel::Fatal, ex.getMessage());
    }

    if (buffer.has_value()) {
    	words = TextUtils::splitTextIntoWords(*buffer);

    }
}



