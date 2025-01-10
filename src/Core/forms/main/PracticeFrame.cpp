//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <windows.h>
#include <algorithm>

#include "TextSource.h"
#include "PracticeFrame.h"
#include "Generator.h"

#include "UIUtils.h"
#include "TextUtils.h"
#include "EnumUtils.h"
#include "FileUtils.h"
#include "CryptoUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KeyboardFrame"
#pragma link "TypingStatsFrame"
#pragma link "TypingTextFrame"
#pragma resource "*.dfm"

TFrPractice *FrPractice;
//---------------------------------------------------------------------------
__fastcall TFrPractice::TFrPractice(TComponent* Owner) : TFrame(Owner) {}

__fastcall TFrPractice::TFrPractice(TComponent* Owner, Parser* _parser, MainSession *_mainSession, TypingSession *_typingSession, \
	TDataModule1 *_dataModule, AuthenticationService *_authService) : TFrame(Owner) {

	if (_parser && _mainSession && _typingSession && _dataModule && _authService) {

       parser = _parser;
       mainSession = _mainSession;
	   typingSession = _typingSession;
       dataModule = _dataModule;
       authService = _authService;

       FrTypingStats->setMainSession(mainSession);
       FrTypingStats->setTypingSession(typingSession);

       FrTypingText->setMainSession(mainSession);
       FrTypingText->setTypingSession(typingSession);
       FrTypingText->setParser(parser);
       FrTypingText->setFrameTypingStats(FrTypingStats);
       FrTypingText->resetTypingStats();

	   FrTypingText->setTypingSession(typingSession);

	   assignPNGToBtn(BtConfig, FileUtils::createProjectSubDirPath("Images") + "settings.png");

       FrKeyboard->Hide();

       FrKeyboard->setDataModule(dataModule);
       FrKeyboard->setMainSession(mainSession);

       LKeyboardLayout->Font->Color = TColor(0x8B8B00);
       LKeyboardLayout->Caption = "Layout: " + EnumUtils::enumToString<KeyboardLayout>(mainSession->getTypingSettings().getKeyboardLayoutStrings(), mainSession->getTypingSettings().getKeyboardLayout());

       FrKeyboard->Show();

       LOGGER(LogLevel::Debug, "Created practice frame");

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFrPractice::setTextSource(const std::vector<UnicodeString> &wordList, int minChars, int maxChars, int minWords, int maxWords) {

    Generator generator(false, false, false);
    UnicodeString generatedText = generator.generateText(wordList, minChars, maxChars, minWords, maxWords);

    typingSession->setTextSource(TextSource(generatedText));
}



void __fastcall TFrPractice::BtStartQuitClick(TObject *Sender)
{

    if (BtStartQuit->Caption == "Start" || BtStartQuit->Caption == "Pokreni") {

        if (typingSession->getTextSource().getText().IsEmpty()) {

            int wordCount = UIUtils::getButtonCaption(PPracticeType) == "Time" ? 50 : StrToInt(UIUtils::getButtonCaption(PPracticeLimit));
          	setTextSource({"the", "quick", "brown", "fox", "jumps", "over", "lazy", "dog"}, 0, 0, wordCount, wordCount);
        }

        this->SetFocus();

        LPracticeResult->Visible = false;
        LPracticeResultDisplay->Caption = "";

      	typingSession->setSessionStatus(SessionStatus::Initialized);
        FrTypingText->changeSessionView(SessionStatus::Initialized);

        UIUtils::enableChildControls(PPracticeType, false);
        UIUtils::enableChildControls(PPracticeLimit, false);
        BtConfig->Enabled = false;

        typingSession->setVirtualKeyboardVisible(true);

        if (mainSession->getAppSettings().getLanguage() == Language::English) {
           BtStartQuit->Caption = "Quit";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            BtStartQuit->Caption = "Završi";
        }
    }

    else if (BtStartQuit->Caption == "Quit" || BtStartQuit->Caption == "Završi" ) {

        if (mainSession->getAppSettings().getLanguage() == Language::English) {
           BtStartQuit->Caption = "Start";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            BtStartQuit->Caption = "Pokreni";
        }

        UIUtils::enableChildControls(PPracticeType, true);
        UIUtils::enableChildControls(PPracticeLimit, true);
        BtConfig->Enabled = true;

        typingSession->setVirtualKeyboardVisible(false);

        LPracticeResult->Visible = true;
        LPracticeResultDisplay->Font->Color = clSilver;

        if (LPracticeResult->Left == 214) {
            LPracticeResult->Left = LPracticeResult->Left + 20;
            LPracticeResultDisplay->Left = LPracticeResultDisplay->Left + 20;
        }

        if (mainSession->getAppSettings().getLanguage() == Language::English) {
           LPracticeResultDisplay->Caption = "cancelled";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            LPracticeResultDisplay->Caption = " otkazano";
        }

        typingSession->setSessionStatus(SessionStatus::Completed);

        FrTypingText->changeSessionView(SessionStatus::Completed);
        FrTypingText->changeSessionView(SessionStatus::Reset);
    }

}

// display practice options

void __fastcall TFrPractice::BtConfigClick(TObject *Sender)
{
	if (!FPracticeSource) {
		FPracticeSource = std::make_unique<TFPracticeSource>(nullptr, dataModule, mainSession, authService);
    }

    FPracticeSource->Position = poMainFormCenter;

	if (FPracticeSource->ShowModal() == mrOk) {

		int index = FPracticeSource->PCSourceText->ActivePageIndex;
		TTabSheet* activeTab = FPracticeSource->PCSourceText->Pages[index];

		if (activeTab) {

			switch (index) {

				case 0: {
                	typingSession->setTextSource(TextSource(FPracticeSource->GetFrGeneratedText()->MPreview->Text));
                   	break;
                }
                case 1: {
                   	typingSession->setTextSource(TextSource(FPracticeSource->GetFrExternalSources()->MParagraph->Text));
                 	break;
                }
                case 2: {
                    typingSession->setTextSource(TextSource(FPracticeSource->GetFrCustomText()->MText->Text));
                	break;
                }
			default:
				;
			}
		}
	}
    if (FPracticeSource) {
          FPracticeSource.reset();
    }

	this->SetFocus();
}

void TFrPractice::assignPNGToBtn(TBitBtn *button, const UnicodeString &path)
{
    std::unique_ptr<TPngImage> png = std::make_unique<TPngImage>();
    png->LoadFromFile(path);

    std::unique_ptr<TBitmap> bmp = std::make_unique<TBitmap>();
    bmp->PixelFormat = pf32bit;
    bmp->Transparent = true;
    bmp->SetSize(BtConfig->Width, BtConfig->Height);
    int left = (BtConfig->Width - png->Width) / 2 - 1;
    int top = (BtConfig->Height - png->Height) / 2 - 1;

    bmp->Canvas->FillRect(TRect(0, 0, bmp->Width, bmp->Height));
    bmp->Canvas->Draw(left, top, png.get());

    button->Glyph->Assign(bmp.get());
}


void TFrPractice::highlightKey(wchar_t wch, bool keyDown) {

	UnicodeString keyCaption = "";

    if (typingSession->isVirtualKeyboardVisible()) {

        if (wch == 0x20) {
           keyCaption = "Space";
        }
        else if (wch == 0x08) {
            keyCaption = "Bsp";
        }
        else if (wch == 0x0D) {
            keyCaption = "Enter";
        }
        else if (wch == 0x12) {
            keyCaption = "Alt";
        }
        else if (wch == 0xA0) {
            keyCaption = "Lsh";
        }
        else if (wch == 0xA1) {
            keyCaption = "Rsh";
        }
        else if (wch == 0x11) {
            keyCaption = "Ctrl";
        }

        if (iswalpha(wch) && iswlower(wch)) {
          towupper(wch);
        }
    }

    FrKeyboard->highlightKey(keyCaption.IsEmpty() ? wch: keyCaption, keyDown);
}


void TFrPractice::processCharMessages(WPARAM wParam) {

 	FrTypingText->processCharMessages(wParam);

}

// highlight virtual keys when pressed

void __fastcall TFrPractice::WndProc(TMessage &Message) {

	switch (Message.Msg) {

        case WM_KEYDOWN:
            highlightKey(Message.WParam, true);
            break;

        case WM_KEYUP:
  			highlightKey(Message.WParam, false);
            break;

        case WM_CHAR:
			processCharMessages(Message.WParam);
        	break;

       	default:
            TFrame::WndProc(Message);
    }

}

