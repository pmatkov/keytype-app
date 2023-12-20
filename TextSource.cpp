//---------------------------------------------------------------------------



#include "TextSource.h"
//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

TextSource::TextSource() {}

TextSource::TextSource(UnicodeString _text) : text(_text) {}

const UnicodeString& TextSource::getText() const {
	return text;
}

UnicodeString& TextSource::getText() {
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
