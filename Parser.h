//---------------------------------------------------------------------------

#ifndef ParserH
#define ParserH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>


class Parser
{
	private:
		UnicodeString buffer;
		bool bufferingEnabled = false;

	public:
        Parser();
		const UnicodeString& getBuffer() const;
		void setBuffer(const UnicodeString& text);

		const bool& isBufferingEnabled() const;
		void setBufferingEnabled(bool _buffered);

		wchar_t getChar(WPARAM wParam);

		void addChar(wchar_t &wch);
		void deleteChar();

};
#endif
