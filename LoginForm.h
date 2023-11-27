//---------------------------------------------------------------------------

#ifndef LoginFormH
#define LoginFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "LoginManager.h"
#include "SessionModule.h"

//---------------------------------------------------------------------------
class TFLogin : public TForm
{
__published:	// IDE-managed Components
	TLabel *LUsername;
	TLabel *LPassword;
	TEdit *EUsername;
	TEdit *EPassword;
	TButton *BtLogin;
	TButton *BtGuest;
	void __fastcall BtGuestClick(TObject *Sender);

private:	// User declarations
	LoginManager loginManager;
	SessionModule *sessionModule;

public:		// User declarations
	__fastcall TFLogin(TComponent* Owner);
//	__fastcall TFLogin(SessionModule *_sessionModule);
	void setSessionModule(SessionModule *_sessionModule);
};
//---------------------------------------------------------------------------
extern PACKAGE TFLogin *FLogin;
//---------------------------------------------------------------------------
#endif
