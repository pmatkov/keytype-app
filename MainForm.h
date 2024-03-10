//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <vcl.h>

#include <memory>
#include <vector>
#include <windows.h>

#include "MainSession.h"
#include "TypingSession.h"
#include "Parser.h"

#include "PreferencesForm.h"
#include "MainFrame.h"
#include "PracticeFrame.h"


//---------------------------------------------------------------------------


class TFMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *MenuSubitemPracticeNew;
	TMenuItem *MenuItemSettings;
	TMenuItem *MenuSubitemPreferences;
	void __fastcall MenuSubitemPracticeNewClick(TObject *Sender);
	void __fastcall MenuSubitemPreferencesClick(TObject *Sender);

private:	// User declarations

    TFPreferences *FPreferences;
    TFPracticeOptions *FPracticeOptions;
	std::unique_ptr<TFrMain> FrMain;
	std::unique_ptr<TFrPractice> FrPractice;

	std::unique_ptr<MainSession> mainSession;
    std::unique_ptr<TypingSession> typingSession;

    std::unique_ptr<Parser> parser;

    HWND REHandle;

public:		// User declarations

	__fastcall TFMain(TComponent* Owner);

    void setPreferencesForm(TFPreferences *_FPreferences);
    void setPracticeOptionsForm(TFPracticeOptions *_FPracticeOptions);
    void setMainSession(std::unique_ptr<MainSession> _mainSession);

	virtual void __fastcall WndProc(TMessage &Message);
	static LRESULT CALLBACK RESubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

};


//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------

#endif
