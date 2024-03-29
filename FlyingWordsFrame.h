//---------------------------------------------------------------------------

#ifndef FlyingWordsFrameH
#define FlyingWordsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include <vector>
#include <memory>

#include "GameEngine.h"
#include "IDisplay.h"
#include "IGameDisplay.h"

#if !defined(INTFOBJECT_IMPL_IUNKNOWN)
#define INTFOBJECT_IMPL_IUNKNOWN(BASE) \
    ULONG   __stdcall AddRef() { return BASE::_AddRef();} \
    ULONG   __stdcall Release(){ return BASE::_Release();} \
    HRESULT __stdcall QueryInterface(REFIID iid, void** p){ return BASE::QueryInterface(iid, p);}
#endif

class TFrFlyingWords : public TFrame, public IDisplay, public IGameDisplay
{
__published:	// IDE-managed Components
	TLabel *LStart;
	TTimer *Timer1;
	void __fastcall LStartClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
	std::unique_ptr<GameEngine> gameEngine;
    std::vector<std::unique_ptr<TLabel>> LflyingWords;

public:		// User declarations
	__fastcall TFrFlyingWords(TComponent* Owner);

    void setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item);
    void selectItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item);
    void setItemsMultiItemControl(const UnicodeString& componentName, const std::vector<UnicodeString>& items, int selectedIndex);
    void addItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item, int selectedIndex);

    bool createTextControl(const UnicodeString& text, const UnicodeString& color) = 0;
    bool removeTextControl(int index) = 0;
    bool moveTextControl(int index, int x, int y) = 0;

	int getTextHeight(int index);
    int getTextWidth(int index);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrFlyingWords *FrFlyingWords;
//---------------------------------------------------------------------------
#endif
