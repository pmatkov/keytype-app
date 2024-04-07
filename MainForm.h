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
#include "Logger.h"
#include "AuthenticationService.h"

#include "PreferencesForm.h"
#include "MainFrame.h"
#include "PracticeFrame.h"
#include "FlyingWordsFrame.h"


//---------------------------------------------------------------------------


class TFMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *MenuSubitemPracticeNew;
	TMenuItem *MenuItemSettings;
	TMenuItem *MenuSubitemPreferences;
	TMenuItem *MenuItemGames;
	TMenuItem *MenuSubitemFlyingWords;
	void __fastcall MenuSubitemPracticeNewClick(TObject *Sender);
	void __fastcall MenuSubitemPreferencesClick(TObject *Sender);
	void __fastcall MenuSubitemFlyingWordsClick(TObject *Sender);

private:	// User declarations

	std::unique_ptr<TFPreferences> FPreferences;
	std::unique_ptr<TFrMain> FrMain;
	std::unique_ptr<TFrPractice> FrPractice;
	std::unique_ptr<TFrFlyingWords> FrFlyingWords;

	std::unique_ptr<MainSession> mainSession;
    std::unique_ptr<TypingSession> typingSession;
    std::unique_ptr<AuthenticationService> authService;

    std::unique_ptr<Parser> parser;
    Logger &logger;

public:		// User declarations

	__fastcall TFMain(TComponent* Owner);

    void setMainSession(std::unique_ptr<MainSession> _mainSession);
    void setAuthenticationService(std::unique_ptr<AuthenticationService> _authService);

//    void updateSessionStatus(SessionStatus status);
//    void moveCaret(CaretType caretType, int index);
//    void clearCaret(CaretType caretType, int index);
//    void setCaret(CaretType caretType, int index);

	virtual void __fastcall WndProc(TMessage &Message);

};


//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------

#endif
