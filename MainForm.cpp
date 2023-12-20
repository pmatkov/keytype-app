//---------------------------------------------------------------------------

#include <System.UITypes.hpp>

#include "MainForm.h"
#include "UIUtils.h"

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

	UIUtils::createFrame<TFrMain>(FrMain, this);
	UIUtils::createFrame<TFrPractice>(FrPractice, this);

	UIUtils::setFrameVisibility<TFrMain>(FrMain, true);
	UIUtils::setFrameVisibility<TFrPractice>(FrPractice, false);

	REHandle = FrPractice->RETextBox->Handle;
	SetWindowSubclass(REHandle, &RESubclass, 1, reinterpret_cast<DWORD_PTR>(this));

}

void TFMain::setSessionModule(SessionModule *_sessionModule) {

	if (_sessionModule) {
	   sessionModule = _sessionModule;
       FrPractice->setStatusInfo(Initial);
	}

}

SessionModule * TFMain::getSessionModule() {

    return sessionModule;
}


void __fastcall TFMain::WndProc(Messages::TMessage &Message) {

	switch (Message.Msg) {

		case WM_CHAR: {

			wchar_t wch = sessionModule->getIOControl()->getChar(Message.WParam);

			if (wch == SPACE && !sessionModule->getIOControl()->isBufferingEnabled()) {

				if (sessionModule->getSession()->isPaused()) {

					sessionModule->getSession()->setPaused(false);
					FrPractice->setStatusInfo(Resume);
				}
				else {
					FrPractice->setStatusInfo(Start);
				}

				sessionModule->getIOControl()->setBufferingEnabled(true);
			}
			else if (wch && sessionModule->getIOControl()->isBufferingEnabled()) {

				if (wch == sessionModule->getSession()->getTextSource().getCurrentChar()) {

					UIUtils::setCharStyle(FrPractice->RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, fsUnderline, false);

					if (sessionModule->getSession()->isMistake()) {
						UIUtils::setCharColor(FrPractice->RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, clRed);
						sessionModule->getSession()->setMistake(false);
					}
					else  {
						UIUtils::setCharColor(FrPractice->RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, clSilver);
					}

					sessionModule->getSession()->increaseCharIndex();

					UIUtils::setCharStyle(FrPractice->RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, fsUnderline, true);
				}
				else {
					sessionModule->getSession()->setMistake(true);
					UIUtils::setCharStyle(FrPractice->RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, fsUnderline, false);
					UIUtils::setCharColor(FrPractice->RETextBox, sessionModule->getSession()->getTextSource().getCharIndex()-1, clRed);

				}

			}
		}
		break;

		default: {
			TForm::WndProc(Message);
		}
	}

}


// prebaciti u frame???

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

		default:
            return DefSubclassProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

void __fastcall TFMain::MenuSubitemPracticeNewClick(TObject *Sender)
{
	UIUtils::switchFrames<TFrMain, TFrPractice>(FrMain, FrPractice);

}
//---------------------------------------------------------------------------

