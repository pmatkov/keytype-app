//---------------------------------------------------------------------------



#include "TextSource.h"
//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

TextSource::TextSource() {
	text = "The quick brown fox jumps over the lazy dog";
	language = LanguageProfile("English", "EN",  "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	charIndex = 1;
}

TextSource::TextSource(UnicodeString _text) : text(_text)  {
     charIndex = 1;
}

const UnicodeString& TextSource::getText() const {
	return text;
}

const UnicodeString& TextSource::getCurrentWord() const {
	return currentWord;
}

const wchar_t TextSource::getCurrentChar() const {

	 return text[charIndex];
}

const int& TextSource::getCharIndex() const {

	 return charIndex;
}


void TextSource::increaseCharIndex() {
	charIndex++;
}

void TextSource::decreaseCharIndex() {
	charIndex--;
}
