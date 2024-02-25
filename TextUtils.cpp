//---------------------------------------------------------------------------

#include "TextUtils.h"

//---------------------------------------------------------------------------
#pragma hdrstop
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

 UnicodeString TextUtils::trimCharacters(const UnicodeString &text, wchar_t wch) {

    int start = 0;
	int end = text.Length() - 1;

	UnicodeString trimmedText;
	const wchar_t* wstr = text.c_str();

	while (start <= end && wstr[start] == wch) {
        start++;
	}

	while (end >= start && wstr[end] == wch) {
        end--;
	}

    if (start <= end) {
		trimmedText = text.SubString(start + 1, end - start + 1);
	}

	return trimmedText;
 }

std::vector<UnicodeString> TextUtils::splitTextIntoWords(const UnicodeString& line)
{
	if (line.Length()) {

       	TStringList* list = new TStringList;
		std::vector<UnicodeString> tokenList;
		UnicodeString token;

		list->DelimitedText = line;
		list->Delimiter = ' ';

		for (int i = 0; i < list->Count; i++)	{

			token = list->Strings[i];
			tokenList.push_back(token);
		}

		delete list;

		return tokenList;
	}
	else {
		return std::vector<UnicodeString>();
    }

}

bool TextUtils::isWordBreak(const UnicodeString& line, int index) {

	return (iswgraph(line[index]) && iswspace(line[index+1])) || iswspace(line[index]) ? true  : false;
}


UnicodeString TextUtils::formatJson(const UnicodeString& string) {

	int i = 0, level = 1;
	bool insidequote = false, openingbracket = false, leveldown = false;
	UnicodeString result = "";
	UnicodeString addfront, addback;

	const wchar_t* wstr = string.c_str();


	while (wstr[i]) {

		addfront = addback = "";

		if (wstr[i] == '[' || wstr[i] == '{') {

			if (wstr[i] == '[') {
				openingbracket = true;
			}

			addback = "\n" + repeatChar(' ', level * 4);
			level++;
			leveldown = false;

		}
		else if (wstr[i] == ']' || wstr[i] == '}') {

			if (wstr[i] == ']' && openingbracket) {
				 level = level - 2;
				 openingbracket = false;
			}
			else {
			   level--;
			}
			addfront = "\n" + repeatChar(' ', level * 4);
			leveldown = true;
		}
		else if (wstr[i] == ',' && !insidequote) {

		   addback = + "\n" + repeatChar(' ', (leveldown ? level : level - 1) * 4);
		   level = leveldown ? level + 1 : level;

		}
		else if (wstr[i] == ':') {
		   addback = " ";
		}
		else if (wstr[i] == '\"') {
			insidequote = !insidequote;
		}

		result += addfront + UnicodeString(wstr[i]) + addback;
		i++;
	}

	return result;

}

UnicodeString TextUtils::repeatChar(wchar_t wch, int count) {

	UnicodeString result = "";

	for (int i = 0; i < count; i++) {
		result += wch;
	}
	return result;
}


int TextUtils::findString(const std::vector<UnicodeString> &vec, const UnicodeString &string) {

    std::vector<UnicodeString>::const_iterator it = std::find(vec.begin(), vec.end(), string);


    if (it != vec.end())  {
        return it - vec.begin();
    }
    else {
        return -1;
    }
}

