//---------------------------------------------------------------------------

#pragma hdrstop

#include "Parser.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

Parser::Parser() {

	LOGGER(LogLevel::Debug, "Parser created");
}

 const UnicodeString& Parser::getBuffer() const {
	 return buffer;
 }

 void Parser::setBuffer(const UnicodeString& text) {
	buffer = text;
}

const bool& Parser::isBufferingEnabled() const {
	return bufferingEnabled;
}

void Parser::setBufferingEnabled(bool _bufferingEnabled) {
	bufferingEnabled = _bufferingEnabled;
}


wchar_t Parser::getChar(WPARAM wParam){

	wchar_t wch = static_cast<wchar_t>(wParam);

	switch (wParam) {

		case VK_RETURN:
		case VK_TAB:
		case VK_ESCAPE:
			break;

		case VK_BACK:{
			if (bufferingEnabled && buffer.Length() > 0) {
            	buffer.Delete(buffer.Length(), 1);
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

void Parser::addChar(wchar_t &wch) {

	buffer += UnicodeString(wch);
}

void Parser::deleteChar() {

	if (buffer.Length() > 0) {
		buffer.Delete(buffer.Length(), 1);
	}
}
