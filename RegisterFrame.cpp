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

    	LOGGER(LogLevel::Debug, "Register frame created");
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
            LOGGER(LogLevel::Info, "User registered as <" + EUsername->Text + ">");
            OnRegister(this, mrOk);
        }

    } else {

        if (!usernameAvailable) {
        	LResponse->Caption = "Username unavailable";
            LOGGER(LogLevel::Debug, "Username unavailable");
        }
        else {
        	LResponse->Caption = "Registration unsuccessful";
        	LOGGER(LogLevel::Debug, "Registration unsuccessful");
        }
    }
}


//  event handler
void __fastcall TFrRegister::FrUsernameUnavailable()
{
    usernameAvailable = false;
}

// validate user input

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

void TFrRegister::UpdateRegisterButtonState()
{
    if (EUsername->Text != "" && EPassword->Text != "" && ERepeatPassword->Text != "") {
        if (EPassword->Text.Compare(ERepeatPassword->Text) != 0) {
            LResponse->Caption = "Passwords mismatch";
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

