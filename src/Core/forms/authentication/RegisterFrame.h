//---------------------------------------------------------------------------

#ifndef RegisterFrameH
#define RegisterFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "AuthenticationService.h"

//---------------------------------------------------------------------------
class TFrRegister : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LUsername;
	TEdit *EPassword;
	TLabel *LPassword;
	TEdit *EUsername;
	TEdit *ERepeatPassword;
	TLabel *LRepeatPassword;
	TButton *BtRegister;
	TLabel *LAlreadyRegistered;
	TButton *BtSignIn;
	TLabel *LResponse;
	TCheckBox *CBRestAuth;
	void __fastcall BtSignInClick(TObject *Sender);
	void __fastcall BtRegisterClick(TObject *Sender);
	void __fastcall EUsernameChange(TObject *Sender);
	void __fastcall EPasswordChange(TObject *Sender);
    void __fastcall ERepeatPasswordChange(TObject *Sender);
private:	// User declarations
    AuthenticationService *authenticationService;
    TDataModule1 *dataModule;
    bool usernameAvailable = true;
public:		// User declarations
	__fastcall TFrRegister(TComponent* Owner);
    __fastcall TFrRegister(TComponent* Owner, AuthenticationService *_authenticationService);
    void UpdateRegisterButtonState();

    void __fastcall FrUsernameUnavailable();

    void __fastcall (__closure *OnRegister)(TObject *Sender, TModalResult result);
    void __fastcall (__closure *OnSignInSelect)(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrRegister *FrRegister;
//---------------------------------------------------------------------------
#endif
