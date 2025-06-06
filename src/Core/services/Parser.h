//---------------------------------------------------------------------------

#ifndef ParserH
#define ParserH
//---------------------------------------------------------------------------
#include <vector>
#include <vcl.h>
#include <windows.h>

#include "MainSession.h"
#include "TypingSession.h"
#include "KeyboardFrame.h"

class TFMain;

class Parser {
	private:
     	MainSession *mainSession;
		TypingSession *typingSession;

        std::vector<std::pair<UnicodeString, bool>> keyLog;
		std::vector<std::pair<UnicodeString, bool>> buffer;
        UnicodeString insertedChars = "";

        bool mistakeRecorded = false;
        bool stopOnMistake = false;
		bool inputEnabled = false;

	public:
        Parser(MainSession *_mainSession, TypingSession *_typingSession);

        const std::vector<std::pair<UnicodeString, bool>>& getKeyLog() const;
		void setKeyLog(const std::vector<std::pair<UnicodeString, bool>>& text);

        const std::vector<std::pair<UnicodeString, bool>>& getBuffer() const;
		void setBuffer(const std::vector<std::pair<UnicodeString, bool>>& text);

        const UnicodeString &getInsertedChars() const;

        const bool isLastCharMistake() const;

        bool isStopOnMistake();
        void setStopOnMistake(bool _stopOnMistake);

		const bool& isInputEnabled() const;
		void setInputEnabled(bool _inputEnabled);

        void resetParser();

		wchar_t getChar(WPARAM wParam);


};
#endif
