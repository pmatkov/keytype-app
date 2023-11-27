//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include "OptionsFrame.h"
#include <memory>
#include <vector>
#include <windows.h>

//#include "IOControl.h"
//#include "PracticeSession.h"
#include "SessionModule.h"
#include "OptionsFrame.h"

//---------------------------------------------------------------------------

//class PracticeController;

enum StartControl {
	Initial,
	Start,
	Restart,
	Resume,
    Pause
};

class TFMain : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *RETextBox;
	TLabel *LStart;
	TFrOptions *FrOptions;
	void __fastcall BtOptionsButtonClick(TObject *Sender);

private:	// User declarations
//	std::unique_ptr<IOControl> iocontrol;
//	std::unique_ptr<PracticeSession> session;
	HWND RichEditHandle;
	SessionModule *sessionModule;

public:		// User declarations
	__fastcall TFMain(TComponent* Owner);

	void setSessionModule(SessionModule *_sessionModule);

	void setCharStyle(TRichEdit* richEdit, int charIndex, TFontStyle style, bool status);
	void setCharColor(TRichEdit* richEdit, int charIndex, TColor textColor);
	void setTextColor(TRichEdit* richEdit, TColor textColor);
	void setStatusInfo(StartControl status);

	virtual void __fastcall WndProc(TMessage &Message);
	static LRESULT CALLBACK RichEditSubclass(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

};


//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------

#endif
