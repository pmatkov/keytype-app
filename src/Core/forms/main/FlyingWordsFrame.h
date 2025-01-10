//---------------------------------------------------------------------------

#ifndef FlyingWordsFrameH
#define FlyingWordsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include "FlyingWordsStatsFrame.h"

#include <vector>
#include <queue>
#include <memory>

#include "FlyingWordsStatsFrame.h"
#include "ISingleItemDisplay.h"
#include "IGameDisplay.h"

#if !defined(INTFOBJECT_IMPL_IUNKNOWN)
#define INTFOBJECT_IMPL_IUNKNOWN(BASE) \
    ULONG   __stdcall AddRef() { return BASE::_AddRef();} \
    ULONG   __stdcall Release(){ return BASE::_Release();} \
    HRESULT __stdcall QueryInterface(REFIID iid, void** p){ return BASE::QueryInterface(iid, p);}
#endif

class GameEngine;

class TFrFlyingWords : public TFrame, public ISingleItemDisplay, public IGameDisplay
{

	INTFOBJECT_IMPL_IUNKNOWN(TFrame)

__published:	// IDE-managed Components
	TFrFlyingWordsStats *FrFlyingWordsStats;
	TComboBox *CBWordList;
	TLabel *LWordList;
	TLabel *LTimeLimit;
	TComboBox *CBTime;
	TOpenTextFileDialog *DFileOpen;
	TButton *BtBrowse;
	TButton *BtStartQuit;
	void __fastcall BtStartQuitClick(TObject *Sender);
	void __fastcall BtBrowseClick(TObject *Sender);
	void __fastcall CBWordListChange(TObject *Sender);
	void __fastcall FrFlyingWordsStatsFrameTMsgDisplayTimerTimer(TObject *Sender);

private:	// User declarations

	std::vector<UnicodeString> tlStrings;

	std::unique_ptr<GameEngine> gameEngine;

    std::vector<std::unique_ptr<TLabel>> LFlyingWords;

    std::unique_ptr<std::queue<wchar_t>> keyStrokeQueue;

    std::unique_ptr<TCriticalSection> criticalSection;
    std::unique_ptr<TEvent> keyStrokeEvent;
    std::unique_ptr<TEvent> wordMatchEvent;
    std::unique_ptr<TEvent> terminateEvent;

public:		// User declarations
	__fastcall TFrFlyingWords(TComponent* Owner);
	~TFrFlyingWords();

	GameEngine &getGameEngine();
	std::queue<wchar_t> &getKeyStrokeQueue();
	TCriticalSection &getCriticalSection();
	TEvent &getKeyStrokeEvent();
	TEvent &getWordMatchEvent();
	TEvent &getTerminateEvent();

	void createTextControl(const UnicodeString& text, const UnicodeString& color);
	void removeTextControl(int index);
    void removeAllTextControls();
	void moveTextControl(int index, int x, int y);

	int getTextHeight(int index);
	int getTextWidth(int index);

    void setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item);

    void processCharMessages(WPARAM wParam);
	virtual void __fastcall WndProc(TMessage &Message);

	void cleanupGame(void);


};
//---------------------------------------------------------------------------
extern PACKAGE TFrFlyingWords *FrFlyingWords;
//---------------------------------------------------------------------------
#endif
