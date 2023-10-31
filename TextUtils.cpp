//---------------------------------------------------------------------------

#include "TextUtils.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)


int TextUtils::countSentences(const UnicodeString &text) {

	int i = 0, count = 0;
	bool inSentence = false;

	const wchar_t* wstr = text.c_str();

	while (wstr[i])  {
		if (iswalnum(wstr[i]) && !inSentence) {
			inSentence = true;
			count++;
		}
		else if (isEndChar(wstr[i]) && iswspace(wstr[i+1]) && inSentence) {
			inSentence = false;
		}
        i++;
	  }
	  return count;
}

int TextUtils::countWords(const UnicodeString &text) {

	int i = 0, count = 0;
	bool inWord = false;

	const wchar_t* wstr = text.c_str();

	while (wstr[i])  {
		if (iswalpha(wstr[i]) && !inWord) {
			inWord = true;
			count++;
		}
		else if (iswspace(wstr[i]) && inWord) {
			inWord = false;
		}
		i++;
	  }
	  return count;
}

int TextUtils::countChars(const UnicodeString &text) {

	int i = 0, count = 0;

	const wchar_t* wstr = text.c_str();

	while (wstr[i])  {
		if (iswgraph(wstr[i++]) ) {
			count++;
		}
	}

	return count;
}


bool TextUtils::isEndChar(const wchar_t wch) {
	if  (wch == L'.' || wch == L'!' || wch == L'?')
		return true;
	else
		return false;
}


 UnicodeString TextUtils::trimSpaces(const UnicodeString &text) {

	bool consecutiveSpace = false;

	UnicodeString trimmedText;
	const wchar_t* wstr = text.c_str();

	int i = 0;

	while (wstr[i])  {
		if (std::iswspace(wstr[i])) {
			if (!consecutiveSpace) {
				trimmedText += ' ';
				consecutiveSpace = true;
			}
		}
		else {
			trimmedText += wstr[i];
			consecutiveSpace = false;
		}
		i++;
	}

	return trimmedText.Trim();

 }

