//---------------------------------------------------------------------------



#include "TextSource.h"
//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

TextSource::TextSource() {
	text = "The quick brown fox jumps over the lazy dog";
	language = new LanguageProfile("English", "EN",  "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	currentCharIndex = 1;
}

TextSource::TextSource(UnicodeString _text) : text(_text)  {
     currentCharIndex = 1;
}

const UnicodeString& TextSource::getText() const {
	return text;
}

const UnicodeString& TextSource::getCurrentWord() const {
	return currentWord;
}

const wchar_t TextSource::getCurrentChar() const {

	 return text[currentCharIndex];
}

const int& TextSource::getCurrentCharIndex() const {

	 return currentCharIndex;
}


void TextSource::increaseCurrentCharIndex() {
	currentCharIndex++;
}

void TextSource::decreaseCurrentCharIndex() {
	currentCharIndex--;
}
