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

__fastcall TFrLogin::TFrLogin(TComponent* Owner, AuthenticationService *_authenticationService, TDataModule1 *_dataModule) : TFrame(Owner)  {

	if (_authenticationService && _dataModule) {
	   	authenticationService = _authenticationService;
        dataModule = _dataModule;
    	LOGGER(LogLevel::Debug, "Login frame created");
	}
    else {
        throw ENullPointerException();
    }
}

void __fastcall TFrLogin::BtSignInClick(TObject *Sender)
{
    UnicodeString username = EUsername->Text;
    UnicodeString password = EPassword->Text;

    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    try {
        query->Connection = dataModule->MySQLDBConnection;
        query->SQL->Text = "SELECT * FROM users WHERE username = :username AND password = :password";
        query->Params->ParamByName("username")->AsString = username;
        query->Params->ParamByName("password")->AsString = password;
        query->Open();

        if (!query->IsEmpty()) {
        	if (OnLogin) {
            	LOGGER(LogLevel::Info, "User signed in as <" + username + ">");
         		OnLogin(this, mrOk);
         	}
        } else {
        	LResponse->Caption = "Invalid credentials";
            LOGGER(LogLevel::Debug, "Invalid credentials");
        }
        query->Close();
    } catch (Exception &ex) {
    	LOGGER(LogLevel::Fatal, ex.Message);
    }
}

void __fastcall TFrLogin::BtGuestClick(TObject *Sender)
{

    if (authenticationService->loginUser("guest")) {
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

//---------------------------------------------------------------------------

