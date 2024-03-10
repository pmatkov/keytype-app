//---------------------------------------------------------------------------

#ifndef TextSourceH
#define TextSourceH

#include <vcl.h>

#include "LanguageProfile.h"
//---------------------------------------------------------------------------

class TextSource
{
	private:
		UnicodeString text = "The quick brown fox jumps over the lazy dog";
		UnicodeString currentWord;
		wchar_t currentChar;
		int charIndex = 1;

        int maxChars;

		bool numbers;
		bool punctuation;
		bool special;

	public:
    	TextSource();
		TextSource(UnicodeString _text);

		const UnicodeString& getText() const;
		UnicodeString& getText();

		const UnicodeString& getCurrentWord() const;

        wchar_t operator[](int index) const;

		int getCharIndex() const;
		void increaseCharIndex();
		void decreaseCharIndex();

};
#endif
