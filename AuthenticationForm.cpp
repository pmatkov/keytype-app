//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AuthenticationForm.h"
#include "UIUtils.h"
#include "ENullPointerException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LoginFrame"
#pragma link "LoginFrame"
#pragma link "RegisterFrame"
#pragma resource "*.dfm"
TFAuthentication *FAuthentication;
//---------------------------------------------------------------------------

__fastcall TFAuthentication::TFAuthentication(TComponent* Owner) : TForm(Owner), logger(Logger::getLogger())  {}

__fastcall TFAuthentication::TFAuthentication(TComponent* Owner, AuthenticationService *_authenticationService) : TForm(Owner), logger(Logger::getLogger())  {

	if (_authenticationService) {

	   	authenticationService = _authenticationService;

        // create frames
        FrLogin = UIUtils::createFrame<TFrLogin>(this, authenticationService);
        FrRegister = UIUtils::createFrame<TFrRegister>(this, authenticationService);

        UIUtils::setFrameVisibility<TFrLogin>(FrLogin, true);
        UIUtils::setFrameVisibility<TFrRegister>(FrRegister, false);
        Caption = "Login";

  		FrLogin->OnRegisterSelect = FrLoginRegisterSelect;
        FrLogin->OnLogin = FrLoginSignInComplete;

        FrRegister->OnSignInSelect = FrRegisterSignInSelect;
        FrRegister->OnRegister = FrRegisterRegisterComplete;

  		LOGGER(LogLevel::Debug, "Created authentication form");

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

//  event handlers
void __fastcall TFAuthentication::FrLoginRegisterSelect(TObject *Sender)
{
	UIUtils::switchFrames<TFrLogin, TFrRegister>(FrLogin, FrRegister);
    Caption = "Register";
}

void __fastcall TFAuthentication::FrLoginSignInComplete(TObject *Sender, TModalResult result)
{
    ModalResult = result;
}

void __fastcall TFAuthentication::FrRegisterSignInSelect(TObject *Sender)
{
	UIUtils::switchFrames<TFrRegister, TFrLogin>(FrRegister, FrLogin);
    Caption = "Login";
}

void __fastcall TFAuthentication::FrRegisterRegisterComplete(TObject *Sender, TModalResult result)
{
    ModalResult = result;
}

// add authentication form to the taskbar
void __fastcall TFAuthentication::CreateParams(TCreateParams &Params)
{
    TForm::CreateParams(Params);
    Params.ExStyle = WS_EX_APPWINDOW;
    Params.WndParent = GetDesktopWindow();
}


