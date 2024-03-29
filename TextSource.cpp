//---------------------------------------------------------------------------
#include "TextSource.h"
#include "TextUtils.h"
//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

TextSource::TextSource() {}

TextSource::TextSource(UnicodeString _text) : text(_text) {

    wordCount = TextUtils::countWords(text);
    charCount = text.Length();
}

const UnicodeString& TextSource::getText() const {
	return text;
}

UnicodeString& TextSource::getText() {
	return text;
}

void TextSource::setText(const UnicodeString& _text) {
    text = _text;
    wordCount = TextUtils::countWords(text);
    charCount = text.Length();
}

int TextSource::getWordCount() const {
	return wordCount;
}

int TextSource::getCharCount() const {
	return charCount;
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
