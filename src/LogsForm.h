//---------------------------------------------------------------------------

#ifndef LogsFormH
#define LogsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "AuthenticationService.h"
#include "DataModule.h"
#include <Vcl.ComCtrls.hpp>
#include "uTPLb_BaseNonVisualComponent.hpp"
#include "uTPLb_Codec.hpp"
#include "uTPLb_CryptographicLibrary.hpp"
#include "uTPLb_Signatory.hpp"
#include <System.SysUtils.hpp>

//---------------------------------------------------------------------------
class TFLogs : public TForm
{
__published:	// IDE-managed Components
	TListView *LVLogFiles;
	TMemo *MLogs;
	void __fastcall LVLogFilesSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall LVLogFilesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormActivate(TObject *Sender);

private:	// User declarations
    AuthenticationService *authService;
    TDataModule1 *dataModule;
public:		// User declarations
	__fastcall TFLogs(TComponent* Owner);
    __fastcall TFLogs(TComponent* Owner, AuthenticationService *_authService, TDataModule1 *_dataModule);

    void updateLogBrowser(int index);
};
//---------------------------------------------------------------------------
extern PACKAGE TFLogs *FLogs;
//---------------------------------------------------------------------------
#endif
