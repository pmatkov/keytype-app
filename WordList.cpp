//---------------------------------------------------------------------------

#pragma hdrstop

#include "WordList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const std::vector<UnicodeString>& WordList::getWordList() const {
	return wordList;
}

void WordList::setWordList(const std::vector<UnicodeString>& _wordList) {
    wordList = _wordList;
}
