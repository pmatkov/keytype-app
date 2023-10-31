//---------------------------------------------------------------------------

#ifndef IOControlH
#define IOControlH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

class IOControl
{

	private:
		UnicodeString charBuffer;
		bool bufferingEnabled;
	public:
	const UnicodeString& getCharBuffer() const;
		void setCharBuffer(const UnicodeString& string);
		const bool isBufferingEnabled() const;
		void setBufferingEnabled(bool _bufferingEnabled);

		//wchar_t getChar(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		  wchar_t getChar(WPARAM wParam);

		void appendChar(wchar_t &wch);
		void deleteLastChar();


};
#endif
