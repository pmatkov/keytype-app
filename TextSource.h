//---------------------------------------------------------------------------

#ifndef TextSourceH
#define TextSourceH

#include <vcl.h>

#include "LanguageProfile.h"
//---------------------------------------------------------------------------

class TextSource
{
	// langauge detection, translator api?
	private:
		UnicodeString text;
		LanguageProfile *language;
		UnicodeString currentWord;
		wchar_t currentChar;
		int charIndex;

		bool numbers;
		bool punctuation;
		bool special;

	public:
		TextSource();
		TextSource(UnicodeString _text);
		const UnicodeString& getText() const;
		const UnicodeString& getCurrentWord() const;
		const wchar_t getCurrentChar() const;
		const int& getCharIndex() const;

		void increaseCharIndex();
		void decreaseCharIndex();

};
#endif
