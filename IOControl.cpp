//---------------------------------------------------------------------------

#pragma hdrstop

#include "IOControl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define MAX_LENGTH 1024


 const UnicodeString& IOControl::getCharBuffer() const {
	 return charBuffer;
 }

 void IOControl::setCharBuffer(const UnicodeString& string) {
	charBuffer = string;
}

const bool IOControl::isBufferingEnabled() const {
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

				int length = charBuffer.Length();

				if (length > 0) {
					charBuffer.Delete(length, 1);
				}
			}
			return wch;
		}

		default: {
			if (bufferingEnabled)
				charBuffer += UnicodeString(wch);
			return wch;
		}


	}

	return L'\0';
}


/*
wchar_t IOControl::getChar(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	if (msg == WM_CHAR){

		wchar_t wch = static_cast<wchar_t>(wParam);

		switch (wParam) {

			case VK_RETURN:
			case VK_TAB:
			case VK_ESCAPE:
				break;

			case VK_BACK:{
				if (bufferingEnabled) {

					int length = charBuffer.Length();

					if (length > 0) {
						charBuffer.Delete(length, 1);
					}
				}
				break;
			}

//			case VK_SPACE: {
//				if (!bufferingEnabled)
//					bufferingEnabled = true;
//				break;
//
//			}


			default: {
				if (bufferingEnabled)
					charBuffer += UnicodeString(wch);
				return wch;
			}


		}
	}

	return L'\0';
}

 */

void IOControl::appendChar(wchar_t &wch) {

	charBuffer += UnicodeString(wch);
}

void IOControl::deleteLastChar() {

	int stringLength = charBuffer.Length();

	if (stringLength > 0) {
		charBuffer.Delete(stringLength, 1);
	}
}
