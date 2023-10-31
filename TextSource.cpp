//---------------------------------------------------------------------------

#pragma hdrstop

#include "TextSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TextSource::TextSource() {
	text = L"The quick brown fox jumps over the lazy dog";
	language = new LanguageProfile("English", "EN",  L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	currentCharIndex = 1;
}

const UnicodeString &TextSource::getText() const {
    return text;
}

const UnicodeString TextSource::getCurrentWord() const {
	return L"empty";
}

const wchar_t TextSource::getCurrentChar() const {

	 return text[currentCharIndex];
}

const int TextSource::getCurrentCharIndex() const {

	 return currentCharIndex;
}


void TextSource::increaseCurrentCharIndex() {
	currentCharIndex++;
}

void TextSource::decreaseCurrentCharIndex() {
	currentCharIndex--;
}
