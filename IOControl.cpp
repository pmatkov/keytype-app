//---------------------------------------------------------------------------

#pragma hdrstop

#include "IOControl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


 const UnicodeString& IOControl::getBuffer() const {
	 return buffer;
 }

 void IOControl::setBuffer(const UnicodeString& string) {
	buffer = string;
}

const bool& IOControl::isBufferingEnabled() const {
	return bufferingEnabled;
}

void IOControl::setBufferingEnabled(bool _bufferingEnabled) {
	bufferingEnabled = _bufferingEnabled;
}


wchar_t IOControl::getChar(WPARAM wParam){

	wchar_t wch = static_cast<wchar_t>(wParam);

	switch (wParam) {

		case VK_RETURN:
		case VK_TAB:
		case VK_ESCAPE:
			break;

		case VK_BACK:{

			if (bufferingEnabled) {

				int length = buffer.Length();

				if (length > 0) {
					buffer.Delete(length, 1);
				}
			}
			return wch;
		}

		default: {
			if (bufferingEnabled) {
				buffer += UnicodeString(wch);
            }
			return wch;
		}

	}

	return L'\0';
}


void IOControl::appendChar(wchar_t &wch) {

	buffer += UnicodeString(wch);
}

void IOControl::deleteLastChar() {

	int stringLength = buffer.Length();

	if (stringLength > 0) {
		buffer.Delete(stringLength, 1);
	}
}
