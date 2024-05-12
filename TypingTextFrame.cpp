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

void TFrTypingText::setTypingStatus(SessionStatus status)  {

	int maxChars = TextUtils::countCharsUntilWordBreak(typingSession->getTextSource().getText(), UIUtils::estimateMaxChars(REText));

	switch (status) {

        case Initialized: {

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

            LInfo->Caption = "Press space bar to start the practice";
            LInfo->Visible = true;
            break;
        }
        case Started: {
            UIUtils::setTextColor(REText, clBlack);

            // set caret style

            if (mainSession->getTypingSettings().getCaretType() == CaretType::Block) {
            	UIUtils::setCharBgColor(REText, 0, clSilver);
            }
            else if (mainSession->getTypingSettings().getCaretType() == CaretType::Underline) {
            	UIUtils::setCharStyle(REText, 0, fsUnderline, true);
            }

            // activate the timer
            typingSession->startSessionTimer();
            FrTypingStats->TStatsTimer->Enabled = true;
            FrTypingStats->clearTimerDisplay();
            FrTypingStats->displayStatsItems();

            LInfo->Visible = false;
            break;
        }
        case Restarted: {

			REText->Text = typingSession->getTextSource().getText().SubString(1, maxChars);
            UIUtils::setTextColor(REText, clSilver);
            LInfo->Visible = true;
            break;

        }
        case Resumed: {
        	UIUtils::setTextColor(REText, clBlack);
            int index = typingSession->getTextSource().getCharIndex()-1;
            UIUtils::setCharColor(REText, parser->getBuffer(), index, index + parser->getInsertedChars().Length(), clRed);
            LInfo->Caption = "Press space bar to start the practice";
            LInfo->Visible = false;
            break;

        }
        case Paused: {
          	FrTypingStats->hideStatsItems();
            UIUtils::setTextColor(REText, clSilver);
            LInfo->Caption = "Press space bar to resume the practice";
            LInfo->Visible = true;
            break;
        }
        case Completed: {
            typingSession->stopSessionTimer();
            FrTypingStats->TStatsTimer->Enabled = false;
            break;
        }
        case Cleared: {
        	FrTypingStats->hideStatsItems();
            LInfo->Visible = false;
            REText->Text = "";
            break;
        }
        default:
        ;

        LOGGER(LogLevel::Debug, "Practice status set");
	}

}

void TFrTypingText::changeSessionStatus(SessionStatus status) {

	if (status == SessionStatus::Initialized) {
        typingSession->setSessionStatus(SessionStatus::Started);
        setTypingStatus(SessionStatus::Started);

    	LOGGER(LogLevel::Info, "Typing session started");
	}
	else if (status == SessionStatus::Paused) {
        typingSession->setSessionStatus(SessionStatus::Resumed);
        setTypingStatus(SessionStatus::Resumed);
		setCaret(mainSession->getTypingSettings().getCaretType(), typingSession->getTextSource().getCharIndex()-1);
    }
}

void TFrTypingText::processCharMessages(WPARAM wParam) {

    wchar_t key = parser->getChar(wParam);

    // start and pause typing session

    if (key == SPACE && !parser->isInputEnabled() && typingSession->getSessionStatus() != SessionStatus::Completed && typingSession->getSessionStatus() != SessionStatus::Cleared) {

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

            parser->setInputEnabled(false);

//            typingSession->setSessionStatus(SessionStatus::Completed);
//            setTypingStatus(SessionStatus::Completed);

            LOGGER(LogLevel::Info, "Typing session completed");

            if (OnTypingComplete) {
                OnTypingComplete(this);
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

