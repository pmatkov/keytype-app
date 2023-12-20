//---------------------------------------------------------------------------

#ifndef IOControlH
#define IOControlH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

class IOControl
{

	private:
		UnicodeString buffer;
		bool bufferingEnabled;

	public:
		const UnicodeString& getBuffer() const;
		void setBuffer(const UnicodeString& string);

		const bool& isBufferingEnabled() const;
		void setBufferingEnabled(bool _bufferingEnabled);

		wchar_t getChar(WPARAM wParam);

		void appendChar(wchar_t &wch);
		void deleteChar();


};
#endif
