//---------------------------------------------------------------------------

#ifndef TextUtilsH
#define TextUtilsH

#include <vcl.h>
#include <cwctype>
#include <vector>

class TextUtils
{
	public:
        static int countSentences(const UnicodeString &text);
        static int countWords(const UnicodeString &text);
        static int countChars(const UnicodeString &text);

        static bool isUnicodeString(const UnicodeString &text);
        static bool isEndChar(const wchar_t wchar);
        static UnicodeString trimCharacters(const UnicodeString &text, wchar_t wch);
        static std::vector<UnicodeString> splitTextIntoWords(const UnicodeString& line);
        static UnicodeString formatJson(const UnicodeString& string);
        static UnicodeString repeatChar(wchar_t wch, int count);

        static int findString(const std::vector<UnicodeString> &vec, const UnicodeString &string);
};
//---------------------------------------------------------------------------
#endif
