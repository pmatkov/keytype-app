//---------------------------------------------------------------------------

#pragma hdrstop

#include "WordList.h"
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
