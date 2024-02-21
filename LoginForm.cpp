//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LoginForm.h"
#include "ENullPointerException.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFLogin *FLogin;
//---------------------------------------------------------------------------
__fastcall TFLogin::TFLogin(TComponent* Owner) : TForm(Owner)  {
  	LOGGER(LogLevel::Debug, "Created login form");
}

__fastcall TFLogin::TFLogin(TComponent* Owner, AuthenticationService *_authenticationService) : TForm(Owner)  {

	if (_authenticationService) {
	   	authenticationService = _authenticationService;
    	LOGGER(LogLevel::Debug, "Login form created");
	}
    else {
        throw ENullPointerException();
    }

}

void __fastcall TFLogin::BtGuestClick(TObject *Sender)
{

    if (authenticationService->loginUser("guest")) {
       ModalResult = mrOk;
   }

}
//---------------------------------------------------------------------------

