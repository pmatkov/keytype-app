//---------------------------------------------------------------------------

#ifndef TextUtilsH
#define TextUtilsH

#include <vcl.h>
#include <cwctype>

class TextUtils
{
	public:
		static int countSentences(const UnicodeString &text);
		static int countWords(const UnicodeString &text);
		static int countChars(const UnicodeString &text);

		static bool isUnicodeString(const UnicodeString &text);
		static bool isEndChar(const wchar_t wchar);
        static UnicodeString trimSpaces(const UnicodeString &text);
};
//---------------------------------------------------------------------------
#endif
