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

__fastcall TFrRegister::TFrRegister(TComponent* Owner, AuthenticationService *_authenticationService, TDataModule1 *_dataModule) : TFrame(Owner)  {

	if (_authenticationService) {
	   	authenticationService = _authenticationService;
        dataModule = _dataModule;
    	LOGGER(LogLevel::Debug, "Register frame created");
	}
    else {
        throw ENullPointerException();
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
	UnicodeString username = EUsername->Text;
    UnicodeString password = EPassword->Text;

    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    try {
        query->Connection = dataModule->MySQLDBConnection;
        query->SQL->Text = "SELECT * FROM users WHERE username = :username";
        query->Params->ParamByName("username")->AsString = username;
        query->Open();

        if (query->IsEmpty()) {

            query->Close();
            query->SQL->Text = "INSERT INTO users (username, password) VALUES (:username, :password)";
            query->Params->ParamByName("username")->AsString = username;
            query->Params->ParamByName("password")->AsString = password;
        	query->ExecSQL();

            if (query->RowsAffected > 0) {
            	if (OnRegister) {
                    LOGGER(LogLevel::Info, "User registered  as <" + username + ">");
                    OnRegister(this, mrOk);
         		}
            }
            else {
                 LOGGER(LogLevel::Debug, "Unable to register user");
            }

        } else {
        	LResponse->Caption = "Username unavailable";
            LOGGER(LogLevel::Debug, "Username unavailable");
        }
        query->Close();
    } catch (Exception &ex) {
    	LOGGER(LogLevel::Fatal, ex.Message);
    }

}

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

