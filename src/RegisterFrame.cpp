//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RegisterFrame.h"
#include "ENullPointerException.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrRegister *FrRegister;
//---------------------------------------------------------------------------
__fastcall TFrRegister::TFrRegister(TComponent* Owner) : TFrame(Owner) {}

__fastcall TFrRegister::TFrRegister(TComponent* Owner, AuthenticationService *_authenticationService) : TFrame(Owner)  {

	if (_authenticationService) {
	   	authenticationService = _authenticationService;
        authenticationService->OnUsernameUnavailable = FrUsernameUnavailable;

    	LOGGER(LogLevel::Debug, "Created register frame");
	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFrRegister::BtSignInClick(TObject *Sender)
{
   	if (OnSignInSelect) {
        OnSignInSelect(this);
     }
}

void __fastcall TFrRegister::BtRegisterClick(TObject *Sender)
{

    if (authenticationService->registerUser(EUsername->Text, EPassword->Text)) {

        if (OnRegister) {
            OnRegister(this, mrOk);
        }

    } else {

        if (!usernameAvailable) {
        	LResponse->Caption = "Username not available";
        }
        else {
        	LResponse->Caption = "Registration failed";
        }
    }
}

//  event handler
void __fastcall TFrRegister::FrUsernameUnavailable()
{
    usernameAvailable = false;
}

// validate input

void __fastcall TFrRegister::EUsernameChange(TObject *Sender)
{
	UpdateRegisterButtonState();
}

void __fastcall TFrRegister::EPasswordChange(TObject *Sender)
{
	UpdateRegisterButtonState();
}

void __fastcall TFrRegister::ERepeatPasswordChange(TObject *Sender)
{
	UpdateRegisterButtonState();
}

// enable/ disable register

void TFrRegister::UpdateRegisterButtonState()
{
    if (EUsername->Text != "" && EPassword->Text != "" && ERepeatPassword->Text != "") {
        if (EPassword->Text.Compare(ERepeatPassword->Text) != 0) {
        	BtRegister->Enabled = false;
            LResponse->Caption = "Passwords don't match";
        }
        else {
        	BtRegister->Enabled = true;
            LResponse->Caption = "";}
    }
    else   {
        BtRegister->Enabled = false;
    	LResponse->Caption = "";
    }

}

