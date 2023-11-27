//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LoginForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFLogin *FLogin;
//---------------------------------------------------------------------------
__fastcall TFLogin::TFLogin(TComponent* Owner)
	: TForm(Owner)
{

}

//
//__fastcall TFLogin::TFLogin(SessionModule *_sessionModule): loginManager(_sessionModule) {}
//---------------------------------------------------------------------------
void TFLogin::setSessionModule(SessionModule *_sessionModule) {

	if (_sessionModule) {
	   sessionModule = _sessionModule;

	   loginManager.setSessionModule(sessionModule);
	}

}
void __fastcall TFLogin::BtGuestClick(TObject *Sender)
{
	   if (loginManager.isValidLogin("guest")) {
		   ModalResult = mrOk;
       }
}
//---------------------------------------------------------------------------

