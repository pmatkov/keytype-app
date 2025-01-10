//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LoginFrame.h"
#include "ENullPointerException.h"
#include "UIUtils.h"
#include "Logger.h"

#include <FireDAC.DApt.hpp>
#include <memory>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrLogin *FrLogin;
//---------------------------------------------------------------------------
__fastcall TFrLogin::TFrLogin(TComponent* Owner) : TFrame(Owner){}

__fastcall TFrLogin::TFrLogin(TComponent* Owner, AuthenticationService *_authenticationService) : TFrame(Owner)  {

	if (_authenticationService) {
	   	authenticationService = _authenticationService;
    	LOGGER(LogLevel::Debug, "Created Login frame");
	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFrLogin::BtSignInClick(TObject *Sender)
{

    if (authenticationService->loginUser(EUsername->Text, EPassword->Text)) {

        if (OnLogin) {

            OnLogin(this, mrOk);
        }

    } else {
        LResponse->Caption = "Invalid credentials";
        LOGGER(LogLevel::Debug, "Invalid credentials");
    }

}

void __fastcall TFrLogin::BtGuestClick(TObject *Sender)
{

	if (authenticationService->loginUser("guest", "")) {

         if (OnLogin) {
            OnLogin(this, mrOk);
         }
     }

}

void __fastcall TFrLogin::BtRegisterClick(TObject *Sender)
{
	if (OnRegisterSelect) {
        OnRegisterSelect(this);
     }
}

// validate input

void __fastcall TFrLogin::EUsernameChange(TObject *Sender)
{
	UpdateSignInButtonState();
}


void __fastcall TFrLogin::EPasswordChange(TObject *Sender)
{
	UpdateSignInButtonState();
}

// enable/ disable sign in

void TFrLogin::UpdateSignInButtonState()
{
    if (EUsername->Text != "" && EPassword->Text != "")   {
        BtSignIn->Enabled = true;
    }
    else {
        BtSignIn->Enabled = false;
        LResponse->Caption = "";
    }
}

