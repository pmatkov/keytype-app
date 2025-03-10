//---------------------------------------------------------------------------
#undef UNICODE
#define UNICODE

#pragma hdrstop

#include "TextUtils.h"
#include "FileUtils.h"

#include "TextCasingSOAP.h"
#include "Logger.h"
#include "Stringtable.h"

#include <cstring>

#define MAX_CHARS 256

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace TextUtils {

    int countSentences(const UnicodeString &text) {

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

    int countWords(const UnicodeString &text) {

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

    int countChars(const UnicodeString &text) {

        int i = 0, count = 0;

        const wchar_t* wstr = text.c_str();

        while (wstr[i])  {
            if (iswgraph(wstr[i++]) ) {
                count++;
            }
        }

        return count;
    }


    bool isEndChar(const wchar_t wch) {
        if  (wch == L'.' || wch == L'!' || wch == L'?')
            return true;
        else
            return false;
    }

     UnicodeString trimCharacters(const UnicodeString &text, wchar_t wch) {

        int start = 0;
        int end = text.Length() - 1;

        const wchar_t* textPtr = text.c_str();

       	while (start <= end && textPtr[start] == wch) {
        	start++;
    	}

        while (end >= start && textPtr[end] == wch) {
            end--;
        }

        if (start > end) {
            return L"";
        }

        return text.SubString(start + 1, end - start + 1);

     }

    std::vector<UnicodeString> splitToTokens(const UnicodeString& text, wchar_t delimiter)
    {

    	std::vector<UnicodeString> tokens = {};

        if (text.Length()) {

            std::unique_ptr<TStringList> list = std::make_unique<TStringList>();

            list->Delimiter = delimiter;
            list->DelimitedText = text;

            for (int i = 0; i < list->Count; i++)	{

                if (!list->Strings[i].IsEmpty()) {
            		tokens.push_back(list->Strings[i]);
                }

            }

        }
        return tokens;
    }

    UnicodeString replaceChar(const UnicodeString& text, wchar_t original, wchar_t replacement) {

       UnicodeString result = text;

        for (int i = 1; i <= result.Length(); i++) {
            if (result[i] == original) {
                result[i] = replacement;
            }
        }
        return result;
    }

   // change separator (TextCasing SOAP)

    UnicodeString replaceWordSeparator(const UnicodeString& text, const UnicodeString &separator) {

       	_di_TextCasingSoapType textCasingService = GetTextCasingSoapType();

        UnicodeString result = textCasingService->TitleCaseWordsWithToken(text, separator).LowerCase();

        return result;
    }


    bool isWordBreak(const UnicodeString& text, int index) {

        if (index >= text.Length()) {
           return false;
        }
        else {
        	return iswgraph(text[index]) && iswspace(text[index+1])  ? false : true;
        }
    }

    int countCharsUntilWordBreak(const UnicodeString& text, int index) {

    	while (index && isWordBreak(text, index)) {
        	index--;
        };

        return index;
    }

    UnicodeString generateStringFromChar(wchar_t wch, int count) {

        UnicodeString result = "";

        for (int i = 0; i < count; i++) {
            result += wch;
        }
        return result;
    }


    int findIndex(const std::vector<UnicodeString> &vec, const UnicodeString &string) {

        std::vector<UnicodeString>::const_iterator it = std::find(vec.begin(), vec.end(), string);

        if (it != vec.end())  {
            return it - vec.begin();
        }
        else {
            return -1;
        }
    }

    UnicodeString vectorToString(const std::vector<UnicodeString> &list) {

      UnicodeString string = "";

      for (const UnicodeString &item: list) {
           string += item + " ";
      }
      return string;
    }


    UnicodeString formatJson(const UnicodeString& string) {

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

				addback = "\n" + generateStringFromChar(' ', level * 4);
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
                addfront = "\n" + generateStringFromChar(' ', level * 4);
                leveldown = true;
            }
            else if (wstr[i] == ',' && !insidequote) {

               addback = + "\n" + generateStringFromChar(' ', (leveldown ? level : level - 1) * 4);
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

        LOGGER(LogLevel::Debug, "Formatted string to JSON");

        return result;
	}

	std::vector<UnicodeString> loadTranslatedStrings(const UnicodeString& libName) {

		HINSTANCE Resource;
		std::vector<UnicodeString> translatedStrings = {};

		if ((Resource = LoadLibrary(libName.c_str())) == nullptr) {
			ShowMessage(L"Can't load DLL");
			return translatedStrings;
		}

		wchar_t buffer[MAX_CHARS + 1] = { L'\0' };

		for (int i = 0; i < IDS_COUNT; i++) {

			if (LoadString(Resource, i + 1, buffer, sizeof(buffer) / sizeof(buffer[0])) > 0) {
			   translatedStrings.push_back(buffer);
			}
		}

		FreeLibrary(Resource);

		return translatedStrings;
	}

}

