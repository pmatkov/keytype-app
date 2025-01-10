//---------------------------------------------------------------------------

#ifndef TextUtilsH
#define TextUtilsH

#include <vcl.h>
#include <System.JSON.hpp>
#include <cwctype>
#include <vector>

namespace TextUtils
{

    int countSentences(const UnicodeString &text);
    int countWords(const UnicodeString &text);
    int countChars(const UnicodeString &text);

    bool isUnicodeString(const UnicodeString &text);
    bool isEndChar(const wchar_t wchar);
    UnicodeString trimCharacters(const UnicodeString &text, wchar_t wch);

    std::vector<UnicodeString> splitToTokens(const UnicodeString& text, wchar_t delimiter = ' ');
	UnicodeString replaceChar(const UnicodeString& text, wchar_t original, wchar_t replacement);
    UnicodeString replaceWordSeparator(const UnicodeString& text, const UnicodeString &separator);
    bool isWordBreak(const UnicodeString& line, int index);
    int countCharsUntilWordBreak(const UnicodeString& line, int index);

    UnicodeString generateStringFromChar(wchar_t wch, int count);
    int findIndex(const std::vector<UnicodeString> &vec, const UnicodeString &string);
    UnicodeString vectorToString(const std::vector<UnicodeString> &list);

	UnicodeString formatJson(const UnicodeString& string);

	std::vector<UnicodeString> loadTranslatedStrings(const UnicodeString& libName);

};
//---------------------------------------------------------------------------
#endif
