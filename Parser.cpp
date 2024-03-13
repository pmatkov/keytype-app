//---------------------------------------------------------------------------

#pragma hdrstop

#include "Parser.h"
#include "Logger.h"
#include "ENullPointerException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

Parser::Parser(MainSession *_mainSession, TypingSession *_typingSession) {

	if (_mainSession && _typingSession) {
        mainSession = _mainSession;
        typingSession = _typingSession;

        LOGGER(LogLevel::Debug, "Parser created");

    } else {
        throw ENullPointerException();
    }
}

 const std::vector<std::pair<UnicodeString, bool>>& Parser::getInputLog() const {
	 return inputLog;
 }

 void Parser::setInputLog(const std::vector<std::pair<UnicodeString, bool>>& text) {
	inputLog = text;
}

 const std::vector<std::pair<UnicodeString, bool>>& Parser::getBuffer() const {
	 return buffer;
 }

 void Parser::setBuffer(const std::vector<std::pair<UnicodeString, bool>>& text) {
	buffer = text;
}

const UnicodeString &Parser::getInsertedChars() const {
    return insertedChars;
}

const bool Parser::isLastCharMistake() const {
    if (buffer.size() > 1) {
    	return buffer[buffer.size()-2].second;
    }
    return false;
}

bool Parser::isStopOnMistake() {
    return stopOnMistake;
}
void Parser::setStopOnMistake(bool _stopOnMistake){
    stopOnMistake = _stopOnMistake;
}

const bool& Parser::isInputEnabled() const {
	return inputEnabled;
}

void Parser::setInputEnabled(bool _inputEnabled) {
	inputEnabled = _inputEnabled;
}


wchar_t Parser::getChar(WPARAM wParam){

	wchar_t wch = static_cast<wchar_t>(wParam);

	switch (wParam) {

        // ignore enter, tab and escape
		case VK_RETURN:
		case VK_TAB:
		case VK_ESCAPE:
			break;


        /* correct typing mistakes (these mistakes are inserted in practice text
        only if 'stop on mistake' isn't active)*/

		case VK_BACK:{

            if (inputEnabled && !insertedChars.IsEmpty()) {
            	insertedChars.Delete(insertedChars.Length(), 1);
                return wch;
            }
            break;
        }

		default: {
            if (inputEnabled) {
                try {

                	if (insertedChars.IsEmpty()) {

                        // change word separator to \u25E6
                        if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Dot && typingSession->getTextSource()[typingSession->getTextSource().getCharIndex()] == L'\u25E6') {
                          wch = L'\u25E6';
                        }

                        // input is valid

                        if (wch == typingSession->getTextSource()[typingSession->getTextSource().getCharIndex()]) {

                            inputLog.push_back(std::make_pair(UnicodeString(wch), false));

                            // flag mistakes in buffer
                            if (!mistake) {
                            	buffer.push_back(std::make_pair(UnicodeString(wch), false));
                            }
                            else {
                              	buffer.push_back(std::make_pair(UnicodeString(wch), true));
                                mistake = false;
                            }

                            // count typed words
                            if (wParam == VK_SPACE || typingSession->getTextSource().getCharIndex() == typingSession->getTextSource().getText().Length()) {
                                typingSession->increaseTypedWords();
                            }

                            typingSession->increaseCharIndex();
                            return wch;

                            // input is invalid
                        } else {
                        	inputLog.push_back(std::make_pair(UnicodeString(wch), true));

                            if (mainSession->getTypingSettings().getCountConsecutiveMistakes()) {
                            	typingSession->increaseMistakes();
                            }
                            else {
                                // flag mistake but don't add to buffer yet (only add after input is valid)
                            	if (!mistake) {
                       				typingSession->increaseMistakes();
                               		mistake = true;
                            	}
                            }

                            // insert invalid chars (only if 'stop on mistake' isn't active)
                            if (!mainSession->getTypingSettings().getStopOnMistake()) {
                                insertedChars += UnicodeString(wch);
                            	return wch;
                            }
                        }
                    }else {
                    	insertedChars += UnicodeString(wch);
                        return wch;
                    }

                } catch (Exception &ex) {
                	LOGGER(LogLevel::Fatal, ex.Message);
                }
            }
            else {
            	return wch;
            }
		}
	}
    return L'\0';
}

