//---------------------------------------------------------------------------

#pragma hdrstop

#include "Parser.h"
#include <cwctype>

#include "Logger.h"
#include "ENullPointerException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

Parser::Parser(MainSession *_mainSession, TypingSession *_typingSession) {

	if (_mainSession && _typingSession) {
        mainSession = _mainSession;
        typingSession = _typingSession;

        LOGGER(LogLevel::Debug, "Created parser");

    } else {
        throw CustomExceptions::ENullPointerException();
    }
}

 const std::vector<std::pair<UnicodeString, bool>>& Parser::getKeyLog() const {
	 return keyLog;
 }

 void Parser::setKeyLog(const std::vector<std::pair<UnicodeString, bool>>& text) {
	keyLog = text;
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

// set state to initial values

void Parser::resetParser() {

	setInputEnabled(false);
    keyLog.clear();
	buffer.clear();
	insertedChars = "";
}


wchar_t Parser::getChar(WPARAM wParam){

	wchar_t wch = static_cast<wchar_t>(wParam);

	switch (wParam) {

        // ignore some control keys

		case VK_RETURN:
		case VK_TAB:
		case VK_ESCAPE:
			break;

        // clear mistake (if 'stop on mistake' is unchecked)

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

                        // change word separator

                        if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Dot && typingSession->getTextSource()[typingSession->getTextSource().getCharIndex()] == L'\u25E6') {
                          wch = L'\u25E6';
                        }

                        // correct key

                        if (wch == typingSession->getTextSource()[typingSession->getTextSource().getCharIndex()]) {

                            // log all keys (correct and mistakes)

                            keyLog.push_back(std::make_pair(UnicodeString(wch), false));

                            // add first mistake to buffer

                            if (mistakeRecorded) {
                            	buffer.push_back(std::make_pair(UnicodeString(wch), true));
                                mistakeRecorded = false;
                            }
                            else {
                            	buffer.push_back(std::make_pair(UnicodeString(wch), false));
                            }

                            // increase word count
                            if (wParam == VK_SPACE || typingSession->getTextSource().getCharIndex() == typingSession->getTextSource().getText().Length()) {
                                typingSession->increaseTypedWords();
                            }

                            typingSession->increaseCorrectKey(wch);

                            typingSession->increaseCharIndex();
                            return wch;

                        }
                        // mistake key

                        else {

                            // log all keys (correct and mistakes)

                        	keyLog.push_back(std::make_pair(UnicodeString(wch), true));

                            if (mainSession->getTypingSettings().getCountConsecutiveMistakes()) {

                            	typingSession->increaseMistakes();
                                typingSession->increaseMistakeKey(typingSession->getTextSource()[typingSession->getTextSource().getCharIndex()]);
                            }
                            else {
                                // flag first mistake

                            	if (!mistakeRecorded) {
                       				typingSession->increaseMistakes();
                               		mistakeRecorded = true;

                                    typingSession->increaseMistakeKey(typingSession->getTextSource()[typingSession->getTextSource().getCharIndex()]);
                            	}
                            }

                            // add consecutive mistakes to buffer (if 'stop on mistake' is unchecked)

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

