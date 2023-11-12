//---------------------------------------------------------------------------

#pragma hdrstop

#include "WordInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const UnicodeString& WordInfo::getWord() const {
	   return word;
}

const WordType& WordInfo::getWordType() const {
	   return wordType;
}
