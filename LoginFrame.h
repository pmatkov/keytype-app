//---------------------------------------------------------------------------

#ifndef LoginFrameH
#define LoginFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "AuthenticationService.h"
//#include "DataModule.h"

//---------------------------------------------------------------------------
class TFrLogin : public TFrame
{
__published:	// IDE-managed Components
	TButton *BtRegister;
	TButton *BtGuest;
	TButton *BtSignIn;
	TEdit *EPassword;
	TLabel *LPassword;
	TLabel *LUsername;
	TEdit *EUsername;
	TLabel *LNotRegistered;
	TLabel *LResponse;
	void __fastcall BtGuestClick(TObject *Sender);
	void __fastcall BtRegisterClick(TObject *Sender);
	void __fastcall EUsernameChange(TObject *Sender);
	void __fastcall EPasswordChange(TObject *Sender);
	void __fastcall BtSignInClick(TObject *Sender);
private:	// User declarations
	AuthenticationService *authenticationService;
public:		// User declarations
	__fastcall TFrLogin(TComponent* Owner);
    __fastcall TFrLogin(TComponent* Owner, AuthenticationService *_authenticationService);
    void UpdateSignInButtonState();

    void __fastcall (__closure *OnLogin)(TObject *Sender, TModalResult result);
    void __fastcall (__closure *OnRegisterSelect)(TObject *Sender);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrLogin *FrLogin;
//---------------------------------------------------------------------------
#endif
