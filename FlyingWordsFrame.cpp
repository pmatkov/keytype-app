//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FlyingWordsFrame.h"
#include "Factory.h"
#include "GameEngine.h"
#include "UIUtils.h"
#include "GameThread.h"

#define ENTER 0x0D

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FlyingWordsStatsFrame"
#pragma link "FlyingWordsStatsFrame"
#pragma resource "*.dfm"

TFrFlyingWords *FrFlyingWords;
//---------------------------------------------------------------------------
__fastcall TFrFlyingWords::TFrFlyingWords(TComponent* Owner) : TFrame(Owner), gameEngine(ModelFactory::createGameEngine(*this, *this)) {

	keyStrokeQueue = std::make_unique<std::queue<wchar_t>>();
    criticalSection = std::make_unique<TCriticalSection>();
    keyStrokeEvent = std::make_unique<TEvent>(nullptr, false, false, "KsEvent", false);
    wordMatchEvent = std::make_unique<TEvent>(nullptr, false, false, "WmEvent", false);
    terminateEvent = std::make_unique<TEvent>(nullptr, true, false, "TeEvent", false);

    LOGGER(LogLevel::Debug, "Flying words frame displayed");
}

 TFrFlyingWords::~TFrFlyingWords() {

 	terminateEvent->SetEvent();
 	gameEngine->threadTerminate();
    terminateEvent->ResetEvent();
    gameEngine->gameCleanup();
 }

 GameEngine &TFrFlyingWords::getGameEngine() {
	 return *gameEngine;
 }

 std::queue<wchar_t> &TFrFlyingWords::getKeyStrokeQueue() {
	 return *keyStrokeQueue;
 }

 TCriticalSection &TFrFlyingWords::getCriticalSection() {
	 return *criticalSection;
 }

 TEvent &TFrFlyingWords::getKeyStrokeEvent() {
 	return *keyStrokeEvent;
 }

 TEvent &TFrFlyingWords::getWordMatchEvent() {
 	return *wordMatchEvent;
 }

 TEvent &TFrFlyingWords::getTerminateEvent() {
 	return *terminateEvent;
 }

void __fastcall TFrFlyingWords::BtStartQuitClick(TObject *Sender)
{
	if (BtStartQuit->Caption == "Start game") {

        if (CBWordList->Text.IsEmpty()) {
        	ShowMessage("Select word list");
        }
        else if (!gameEngine->isWordListLoaded()) {
        	ShowMessage("Word list is empty");
        }
        else{
        	BtStartQuit->Caption = "Quit game";
            this->SetFocus();
            UIUtils::showChildControls(FrFlyingWordsStats, true);
            CBWordList->Enabled = false;
            BtBrowse->Enabled = false;
            CBTime->Enabled = false;

            gameEngine->initializeGame(FWLimit::Limit(FrFlyingWordsStats->Height + 10, BtStartQuit->Top - 10, 0, this->ClientWidth));
        }
	}
    else if (BtStartQuit->Caption == "Quit game") {
        BtStartQuit->Caption = "Start game";
        UIUtils::showChildControls(FrFlyingWordsStats, false);
        CBWordList->Enabled = true;
        BtBrowse->Enabled = true;
        CBTime->Enabled = true;

        terminateEvent->SetEvent();
        gameEngine->threadTerminate();
        terminateEvent->ResetEvent();
        gameEngine->gameCleanup();
    }

}

void TFrFlyingWords::createTextControl(const UnicodeString& text, const UnicodeString& color) {

    std::unique_ptr<TLabel> label = std::make_unique<TLabel>(this);
    label->Parent = this;
    label->Font->Color = StringToColor(color);
    label->Caption = text;
    label->Font->Size = 10;

    LFlyingWords.push_back(std::move(label));
}

void TFrFlyingWords::removeTextControl(int index) {

	if (index >= 0 && index < LFlyingWords.size()) {
		LFlyingWords.erase(LFlyingWords.begin() + index);
	}
}

void TFrFlyingWords::removeAllTextControls() {

	LFlyingWords.clear();
}

void TFrFlyingWords::moveTextControl(int index, int x, int y) {

	if (index >= 0 && index < LFlyingWords.size()) {

    	LFlyingWords[index]->Top = y;
		LFlyingWords[index]->Left = x;
	}
}


int TFrFlyingWords::getTextHeight(int index) {
     return LFlyingWords[index]->Height;
}

int TFrFlyingWords::getTextWidth(int index) {
	 return LFlyingWords[index]->Width;
}

void __fastcall TFrFlyingWords::BtBrowseClick(TObject *Sender) {

    UIUtils::setFileDialogProperties(DFileOpen, "WordList", "txt");

    if (DFileOpen->Execute()) {

         if (FileExists(DFileOpen->FileName)) {

              // extracts filename and extension from path
             UnicodeString filename = ExtractFileName(DFileOpen->FileName);

             if (CBWordList->Items->IndexOf(filename) == -1) {

                CBWordList->Items->Add(filename);
                CBWordList->ItemIndex = CBWordList->Items->Count - 1;
                gameEngine->loadWordList(CBWordList->Text);

             }
         }
    }
    this->SetFocus();
}

void __fastcall TFrFlyingWords::CBWordListChange(TObject *Sender)
{
	gameEngine->loadWordList(CBWordList->Text);
}

void TFrFlyingWords::setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item) {

    if (componentName == "LastWord") {
    	FrFlyingWordsStats->LLastWordDisplay->Caption = item;
    	UIUtils::higlightMessage(FrFlyingWordsStats->TMsgDisplayTimer, FrFlyingWordsStats->LLastWordDisplay, clRed);
    }
    else if (componentName == "MatchCount") {
    	FrFlyingWordsStats->LMatchCountDisplay->Caption = item;
    }
    else if (componentName == "TimeRemaining") {
    	FrFlyingWordsStats->LTimeRemainingDisplay->Caption = item;
    }
    else if (componentName == "Points") {
    	FrFlyingWordsStats->LPointsDisplay->Caption = item;
    }
}


void TFrFlyingWords::processCharMessages(WPARAM wParam) {

    if (gameEngine->getGameStatus() == GameStatus::Started) {

      	wchar_t key = static_cast<wchar_t>(wParam);

    	criticalSection->Acquire();
        if (key != ENTER) {
           keyStrokeQueue->push(key);
        }
     	criticalSection->Release();

        if (keyStrokeQueue->size() && key == ENTER) {
        	keyStrokeEvent->SetEvent();
        }

    }
}


void __fastcall TFrFlyingWords::WndProc(Messages::TMessage &Message) {

    switch (Message.Msg) {

        case WM_CHAR: {
            processCharMessages(Message.WParam);
            break;
        }
        default: {
            TFrame::WndProc(Message);
        }
	}
}


void __fastcall TFrFlyingWords::FrFlyingWordsStatsFrameTMsgDisplayTimerTimer(TObject *Sender)

{
  	UIUtils::removeHiglightMessage(FrFlyingWordsStats->TMsgDisplayTimer, FrFlyingWordsStats->LLastWordDisplay);
}
//---------------------------------------------------------------------------

