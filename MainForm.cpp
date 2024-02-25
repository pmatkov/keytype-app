//---------------------------------------------------------------------------

#include <System.UITypes.hpp>

#include "MainForm.h"
#include "UIUtils.h"
#include "ENullPointerException.h"
#include "Logger.h"

#define SPACE 0x20

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma link "MainFrame"
#pragma link "PracticeFrame"
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner) {

    parser = std::make_unique<Parser>();
	practiceSession = std::make_unique<PracticeSession>();

    // create frames
	FrMain = UIUtils::createFrame<TFrMain>(this);
	FrPractice = UIUtils::createFrame<TFrPractice>(this, parser.get(), practiceSession.get());

	UIUtils::setFrameVisibility<TFrMain>(FrMain, true);
	UIUtils::setFrameVisibility<TFrPractice>(FrPractice, false);

//  set subclass procedure for Rich Edit control (practice text)
	REHandle = FrPractice->RETextBox->Handle;
	SetWindowSubclass(REHandle, &RESubclass, 1, reinterpret_cast<DWORD_PTR>(this));

    LOGGER(LogLevel::Debug, "Created main form");
}

void TFMain::setMainSession(std::unique_ptr<MainSession> _mainSession) {

    if (_mainSession) {
       mainSession = std::move(_mainSession);
       LOGGER(LogLevel::Debug, "Main session moved");
    }
    else {
        throw ENullPointerException();
    }
}

const MainSession * TFMain::getMainSession() const {

    return mainSession.get();
}

const PracticeSession * TFMain::getPracticeSession() const {

    return practiceSession.get();
}

void TFMain::setPreferencesForm(TFPreferences *_FPreferences) {

    if (_FPreferences) {
    	FPreferences =_FPreferences;
    }
}

void TFMain::setPracticeForm(TFPractice *FPractice) {

    if (FrPractice) {
    	FrPractice->setPracticeForm(FPractice);
    }
}


// process char messages

void __fastcall TFMain::WndProc(Messages::TMessage &Message) {

    switch (Message.Msg) {

        case WM_CHAR: {

            wchar_t key = parser->getChar(Message.WParam);

            // start and pause practice session

            if (key == SPACE && !parser->isBufferingEnabled()) {

                if (practiceSession->isPaused()) {
                    practiceSession->setPaused(false);
                    FrPractice->setPracticeStatus(Resumed);
                    LOGGER(LogLevel::Debug, "Practice session resumed");
                }
                else {
                    FrPractice->setPracticeStatus(Started);

                    FrPractice->RETextBox->SetFocus();
                    FrPractice->RETextBox->SelStart = 0;
                    FrPractice->RETextBox->SelLength = 0;

                    LOGGER(LogLevel::Info, "Practice session started");
                }

                parser->setBufferingEnabled(true);
            }
            else if (key && parser->isBufferingEnabled()) {

                // check if the correct key was pressed

                wchar_t currentChar = practiceSession->getTextSource().getCurrentChar();
                int currCharIndex = practiceSession->getTextSource().getCharIndex()-1;

            	UIUtils::setCharStyle(FrPractice->RETextBox, currCharIndex, fsUnderline, false);

                if (key == currentChar) {

                	// if the correct key was pressed remove underline and set color

                    if (practiceSession->isMistake()) {
                        practiceSession->setMistake(false);
                    }
                    else  {

                        UIUtils::setCharColor(FrPractice->RETextBox, currCharIndex, clSilver);
                    }

                    practiceSession->increaseCharIndex();
                    UIUtils::setCharStyle(FrPractice->RETextBox, currCharIndex + 1, fsUnderline, true);
                }
                else {
                    // if the wrong key was pressed remove underline and set color

                    practiceSession->setMistake(true);
                    UIUtils::setCharColor(FrPractice->RETextBox, currCharIndex, clRed);
                }
                 FrPractice->RETextBox->SelStart = currCharIndex + 1;
            }
        }
        break;

        default: {
            TForm::WndProc(Message);
        }
    }
}

/* 	intercept messages intended for Rich Edit control
 	hide caret when typing and display arrow cursor on hover
 	forward char messages to parent control (main form)  */

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
        case WM_LBUTTONUP:
        case WM_MOUSEMOVE:
            return 0;

		default:
            return DefSubclassProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

//  create practice session

void __fastcall TFMain::MenuSubitemPracticeNewClick(TObject *Sender)
{
    practiceSession->setActive(true);

	UIUtils::switchFrames<TFrMain, TFrPractice>(FrMain, FrPractice);
    LOGGER(LogLevel::Debug, "Switch control to practice frame");

}
//---------------------------------------------------------------------------

void __fastcall TFMain::MenuSubitemPreferencesClick(TObject *Sender)
{

    if (FPreferences->ShowModal() == mrOk) {
    	LOGGER(LogLevel::Debug, "Preferences displayed");
    }


}
//---------------------------------------------------------------------------

