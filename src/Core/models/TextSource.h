//---------------------------------------------------------------------------

#ifndef TextSourceH
#define TextSourceH

#include <vcl.h>

//---------------------------------------------------------------------------

class TextSource
{
	private:
		UnicodeString text = "";

        int wordCount = 0;
        int charCount = 0;

		UnicodeString currentWord;
		wchar_t currentChar;
		int charIndex = 1;

	public:
    	TextSource();
		TextSource(UnicodeString _text);

		const UnicodeString& getText() const;
		UnicodeString& getText();
        void setText(const UnicodeString& _text);

        int getWordCount() const;
        int getCharCount() const;

		const UnicodeString& getCurrentWord() const;

        wchar_t operator[](int index) const;

		int getCharIndex() const;
		void increaseCharIndex();
		void decreaseCharIndex();

};
#endif
