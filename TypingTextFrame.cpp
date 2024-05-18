//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TypingTextFrame.h"
#include "UIUtils.h"
#include "TextUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"

#define SPACE 0x20
#define BACKSPACE 0x8

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrTypingText *FrTypingText;
//---------------------------------------------------------------------------
__fastcall TFrTypingText::TFrTypingText(TComponent* Owner) : TFrame(Owner) {}

void TFrTypingText::setMainSession(MainSession *_mainSession) {
   mainSession = _mainSession;
}

void TFrTypingText::setTypingSession(TypingSession *_typingSession) {
   typingSession = _typingSession;
}

void TFrTypingText::setParser(Parser *_parser) {
   parser = _parser;
}

void TFrTypingText::setFrameTypingStats(TFrTypingStats *_FrTypingStats) {
   FrTypingStats = _FrTypingStats;
}

void TFrTypingText::changeSessionView(SessionStatus status)  {

	switch (status) {

        case SessionStatus::Initialized: {

        	int maxChars = TextUtils::countCharsUntilWordBreak(typingSession->getTextSource().getText(), UIUtils::estimateMaxChars(REText));

            FrTypingStats->hideStatsItems();

			// fix font change at runtime
            REText->Font->Name = mainSession->getTypingSettings().getFontFamily();
            REText->Font->Size = mainSession->getTypingSettings().getFontSize();

//            ShowMessage(StrToInt( REText->Font->Size));

            // set text source and color

			UnicodeString sourceText = typingSession->getTextSource().getText();
            UIUtils::setTextColor(REText, clSilver);

			if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Space) {
            	REText->Text = sourceText.SubString(1, maxChars);
            }
            else if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Dot) {
				REText->Text = TextUtils::replaceChar(sourceText.SubString(1, maxChars), ' ', L'\u25E6');
            }

            LPrompt->Caption = "Press space bar to start the practice";
            LPrompt->Visible = true;
            break;
        }
        case SessionStatus::Started: {

            UIUtils::setTextColor(REText, clBlack);

            // set caret style

            if (mainSession->getTypingSettings().getCaretType() == CaretType::Block) {
            	UIUtils::setCharBgColor(REText, 0, clSilver);
            }
            else if (mainSession->getTypingSettings().getCaretType() == CaretType::Underline) {
            	UIUtils::setCharStyle(REText, 0, fsUnderline, true);
            }

            typingSession->initializeSession();
            FrTypingStats->TStatsTimer->Enabled = true;
            initializeTypingStats();

            LPrompt->Visible = false;
            break;
        }
        case SessionStatus::Completed: {

           	typingSession->resetSession();
            parser->resetParser();
            FrTypingStats->TStatsTimer->Enabled = false;

            break;
        }

        case SessionStatus::Reset: {
        	resetTypingStats();

            LPrompt->Visible = false;
            REText->Text = "";
            break;
        }
        default:
        ;

        LOGGER(LogLevel::Debug, "Typing status changed");
	}
}


void TFrTypingText::changeSessionStatus(SessionStatus status) {

	if (status == SessionStatus::Initialized) {
        typingSession->setSessionStatus(SessionStatus::Started);
        changeSessionView(SessionStatus::Started);

    	LOGGER(LogLevel::Info, "Typing session started");
	}
}

void TFrTypingText::initializeTypingStats() {

    FrTypingStats->clearTimerDisplay();
    FrTypingStats->displayStatsItems();
}

void TFrTypingText::resetTypingStats() {

	FrTypingStats->hideStatsItems();
}

void TFrTypingText::processCharMessages(WPARAM wParam) {

    wchar_t key = parser->getChar(wParam);

    // start and pause typing session

    if (key == SPACE && !parser->isInputEnabled() && typingSession->getSessionStatus() != SessionStatus::Completed) {

        changeSessionStatus(typingSession->getSessionStatus());
        parser->setInputEnabled(true);
    }
    else if (key && parser->isInputEnabled()) {

        int index = typingSession->getTextSource().getCharIndex()-1;

        // highlight mistakes

        if (parser->getInsertedChars().IsEmpty()) {
            UIUtils::setCharColor(REText, parser->getBuffer(), clRed);
        }

        // insert chars on mistake (only if 'stop on mistake' isn't checked)

        if (key == BACKSPACE || !parser->getInsertedChars().IsEmpty()) {

            UnicodeString text = "";
            if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Space) {
                text = typingSession->getTextSource().getText();
            }
            else if (mainSession->getTypingSettings().getSeparatorType() == SeparatorType::Dot) {
                text = TextUtils::replaceChar(typingSession->getTextSource().getText(), ' ', L'\u25E6');
            }

            // recalculate max chars for REText based on inserted chars

            text.Insert(parser->getInsertedChars(), index+1);
            int maxChars = TextUtils::countCharsUntilWordBreak(typingSession->getTextSource().getText(), UIUtils::estimateMaxChars(REText));
            REText->Text = text.SubString(1, maxChars);
            UIUtils::setCharColor(REText, parser->getBuffer(), index, index + parser->getInsertedChars().Length(), clRed);
        }

        // move caret to the next char
        moveCaret(mainSession->getTypingSettings().getCaretType(), index);

        // end typing session if last char reached

        if (typingSession->getTextSource().getCharIndex()-1 == typingSession->getTextSource().getText().Length()) {

            if (typingSession->getSessionType() == SessionType::Lesson && OnLessonComplete) {

            	LOGGER(LogLevel::Info, "Typing session completed");
                OnLessonComplete(this);
             }
        }
    }
}

void TFrTypingText::moveCaret(CaretType caretType, int index) {

	if (caretType == CaretType::Block) {
        UIUtils::setCharBgColor(REText, index + parser->getInsertedChars().Length() - 1, clBtnFace);
        UIUtils::setCharBgColor(REText, index + parser->getInsertedChars().Length(), clSilver);
	}
    else if (caretType == CaretType::Underline) {
        UIUtils::setCharStyle(REText, index + parser->getInsertedChars().Length() - 1, fsUnderline, false);
		UIUtils::setCharStyle(REText, index + parser->getInsertedChars().Length(), fsUnderline, true);
    }
}

void TFrTypingText::clearCaret(CaretType caretType, int index) {

	if (caretType == CaretType::Block) {
        UIUtils::setCharBgColor(REText, index + parser->getInsertedChars().Length(), clBtnFace);
    }
	else if (caretType == CaretType::Underline) {
		UIUtils::setCharStyle(REText, index + parser->getInsertedChars().Length(), fsUnderline, false);
	}
}

void TFrTypingText::setCaret(CaretType caretType, int index) {

	if (caretType == CaretType::Block) {
		UIUtils::setCharBgColor(REText, index + parser->getInsertedChars().Length(), clSilver);
	}
	else if (caretType == CaretType::Underline) {
		UIUtils::setCharStyle(REText, index + parser->getInsertedChars().Length(), fsUnderline, true);
	}
}


LRESULT CALLBACK TFrTypingText::RESubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{

	switch (msg) {

		case WM_SETFOCUS:
			HideCaret(hwnd);
			break;

		case WM_KILLFOCUS:
			ShowCaret(hwnd);
			break;

		case WM_SETCURSOR:
			Screen->Cursor = crArrow;
			return TRUE;

		case WM_CHAR:
			PostMessage(GetParent(hwnd), WM_CHAR, wParam, lParam);
			break;

        case WM_LBUTTONDOWN:
            break;

		default:
			return DefSubclassProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

