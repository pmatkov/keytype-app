//---------------------------------------------------------------------------

#include <vcl.h>
#include <memory>

#pragma hdrstop

#include "LoginFrame.h"
#include "ENullPointerException.h"
#include "UIUtils.h"
#include "Logger.h"
#include <FireDAC.DApt.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrLogin *FrLogin;
//---------------------------------------------------------------------------
__fastcall TFrLogin::TFrLogin(TComponent* Owner) : TFrame(Owner){}

__fastcall TFrLogin::TFrLogin(TComponent* Owner, AuthenticationService *_authenticationService) : TFrame(Owner)  {

	if (_authenticationService) {
	   	authenticationService = _authenticationService;
    	LOGGER(LogLevel::Debug, "Login frame created");
	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFrLogin::BtSignInClick(TObject *Sender)
{

    if (authenticationService->loginUser(EUsername->Text, EPassword->Text)) {

        if (OnLogin) {
            LOGGER(LogLevel::Info, "User signed in as <" + EUsername->Text + ">");
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
            LOGGER(LogLevel::Info, "User signed in as <guest>");
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

void __fastcall TFrLogin::EUsernameChange(TObject *Sender)
{
	UpdateSignInButtonState();
}


void __fastcall TFrLogin::EPasswordChange(TObject *Sender)
{
	UpdateSignInButtonState();
}

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

