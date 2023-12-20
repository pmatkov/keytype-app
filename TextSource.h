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

		bool numbers;
		bool punctuation;
		bool special;

	public:
    	TextSource();
		TextSource(UnicodeString _text);
		const UnicodeString& getText() const;
		UnicodeString& getText();
		const UnicodeString& getCurrentWord() const;
		const wchar_t getCurrentChar() const;
		const int& getCharIndex() const;

		void increaseCharIndex();
		void decreaseCharIndex();

};
#endif
