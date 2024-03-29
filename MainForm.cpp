//---------------------------------------------------------------------------

#include "MainForm.h"
#include "UIUtils.h"
#include "TextUtils.h"
#include "ENullPointerException.h"

#define SPACE 0x20
#define BACKSPACE 0x8

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma link "MainFrame"
#pragma link "PracticeFrame"
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner), logger(Logger::getLogger())  {

    // create frames
	FrMain = UIUtils::createFrame<TFrMain>(this);

	UIUtils::setFrameVisibility<TFrMain>(FrMain, true);

    LOGGER(LogLevel::Debug, "Created main form");

}


void TFMain::setMainSession(std::unique_ptr<MainSession> _mainSession) {

    if (_mainSession) {
      	mainSession = std::move(_mainSession);

		UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());
        UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());

       	LOGGER(LogLevel::Debug, "Main session moved");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFMain::setAuthenticationService(std::unique_ptr<AuthenticationService> _authService) {

    if (_authService) {
      	authService = std::move(_authService);

       	LOGGER(LogLevel::Debug, "Main session moved");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

// process input and update UI

void __fastcall TFMain::WndProc(Messages::TMessage &Message) {

    switch (Message.Msg) {

        case WM_CHAR: {

            wchar_t key = parser->getChar(Message.WParam);

            // start and pause typing session

            if (key == SPACE && !parser->isInputEnabled()) {

            	updateSessionStatus(typingSession->getSessionStatus());
                parser->setInputEnabled(true);
            }
            else if (key && parser->isInputEnabled()) {

            	int index = typingSession->getTextSource().getCharIndex()-1;
                // highlight mistakes

                if (parser->getInsertedChars().IsEmpty()) {
       				UIUtils::setCharColor(FrPractice->RETextBox, parser->getBuffer(), clRed);
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

                    // recalculate max chars for RETextBox based on inserted chars

					text.Insert(parser->getInsertedChars(), index+1);
                    int maxChars = TextUtils::countCharsUntilWordBreak(typingSession->getTextSource().getText(), UIUtils::estimateMaxChars(FrPractice->RETextBox));
                    FrPractice->RETextBox->Text = text.SubString(1, maxChars);
                    UIUtils::setCharColor(FrPractice->RETextBox, parser->getBuffer(), index, index + parser->getInsertedChars().Length(), clRed);
                }

                // move caret to the next char

                moveCaret(mainSession->getTypingSettings().getCaretType(), index);

            }
        }
        break;

        default: {
            TForm::WndProc(Message);
        }
    }
}


void TFMain::updateSessionStatus(SessionStatus status) {

    if (status == SessionStatus::Initialized) {
        typingSession->setSessionStatus(SessionStatus::Started);
        FrPractice->setPracticeStatus(SessionStatus::Started);

    	LOGGER(LogLevel::Info, "Practice session started");
	}
	else if (status == SessionStatus::Paused) {
        typingSession->setSessionStatus(SessionStatus::Resumed);
        FrPractice->setPracticeStatus(SessionStatus::Resumed);
        setCaret(mainSession->getTypingSettings().getCaretType(), typingSession->getTextSource().getCharIndex()-1);
    }
}

void TFMain::moveCaret(CaretType caretType, int index) {

	if (mainSession->getTypingSettings().getCaretType() == CaretType::Block) {
        UIUtils::setCharBgColor(FrPractice->RETextBox, index + parser->getInsertedChars().Length() - 1, clBtnFace);
        UIUtils::setCharBgColor(FrPractice->RETextBox, index + parser->getInsertedChars().Length(), clSilver);
    }
    else if (mainSession->getTypingSettings().getCaretType() == CaretType::Underline) {
        UIUtils::setCharStyle(FrPractice->RETextBox, index + parser->getInsertedChars().Length() - 1, fsUnderline, false);
        UIUtils::setCharStyle(FrPractice->RETextBox, index + parser->getInsertedChars().Length(), fsUnderline, true);
    }
}

void TFMain::clearCaret(CaretType caretType, int index) {

	if (mainSession->getTypingSettings().getCaretType() == CaretType::Block) {
        UIUtils::setCharBgColor(FrPractice->RETextBox, index + parser->getInsertedChars().Length(), clBtnFace);
    }
    else if (mainSession->getTypingSettings().getCaretType() == CaretType::Underline) {
        UIUtils::setCharStyle(FrPractice->RETextBox, index + parser->getInsertedChars().Length(), fsUnderline, false);
    }
}

void TFMain::setCaret(CaretType caretType, int index) {

	if (mainSession->getTypingSettings().getCaretType() == CaretType::Block) {
        UIUtils::setCharBgColor(FrPractice->RETextBox, index + parser->getInsertedChars().Length(), clSilver);
    }
    else if (mainSession->getTypingSettings().getCaretType() == CaretType::Underline) {
        UIUtils::setCharStyle(FrPractice->RETextBox, index + parser->getInsertedChars().Length(), fsUnderline, true);
    }
}

/* 	intercept RETextBox messages,
 	hide caret and display cursor,
 	forward chars to parent */

LRESULT CALLBACK TFMain::RESubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
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

//  create practice session

void __fastcall TFMain::MenuSubitemPracticeNewClick(TObject *Sender)
{

    if (!typingSession && !parser && !FrPractice) {
        typingSession = std::make_unique<TypingSession>();
        parser = std::make_unique<Parser>(mainSession.get(), typingSession.get());

        FrPractice = UIUtils::createFrame<TFrPractice>(this, parser.get(), mainSession.get(), typingSession.get());

        //  set subclass procedure for RETextBox

        REHandle = FrPractice->RETextBox->Handle;
        SetWindowSubclass(REHandle, &RESubclass, 1, reinterpret_cast<DWORD_PTR>(this));
    }
    UIUtils::switchFrames<TFrMain, TFrPractice>(FrMain, FrPractice);
    LOGGER(LogLevel::Debug, "Switch control to practice frame");

}

void __fastcall TFMain::MenuSubitemPreferencesClick(TObject *Sender)
{

    if (!FPreferences) {
        FPreferences = std::make_unique<TFPreferences>(nullptr, mainSession.get(), authService.get());
        FPreferences->Position = poMainFormCenter;
    }

    if (typingSession) {
    typingSession->setSessionStatus(SessionStatus::Paused);
    FrPractice->setPracticeStatus(SessionStatus::Paused);

        clearCaret(mainSession->getTypingSettings().getCaretType(), typingSession->getTextSource().getCharIndex()-1);
        parser->setInputEnabled(false);
    }

    if (FPreferences->ShowModal() == mrOk) {

        if (mainSession->getAppSettings().getLanguageChanged()) {
            UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());
            mainSession->getAppSettings().setLanguageChanged(false);
        }

        if (typingSession) {
            typingSession->setSessionStatus(SessionStatus::Initialized);
            FrPractice->setPracticeStatus(SessionStatus::Initialized);
        }
    }

    LOGGER(LogLevel::Debug, "Preferences displayed");

}

