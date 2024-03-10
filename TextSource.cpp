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


wchar_t TextSource::operator[](int index) const {
   if (index >= 1 && index <= text.Length()) {
        return text[index];
    } else {
        throw std::out_of_range("Index out of bounds");
    }
}

int TextSource::getCharIndex() const {
	 return charIndex;
}


void TextSource::increaseCharIndex() {
	charIndex++;
}

void TextSource::decreaseCharIndex() {
	charIndex--;
}
