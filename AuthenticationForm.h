//---------------------------------------------------------------------------

#ifndef AuthenticationFormH
#define AuthenticationFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LoginFrame.h"
#include "RegisterFrame.h"
#include <memory>

#include "LoginFrame.h"
#include "RegisterFrame.h"
#include "AuthenticationService.h"
#include "DataModule.h"

//---------------------------------------------------------------------------
class TFAuthentication : public TForm
{
    __published:	// IDE-managed Components

    private:	// User declarations
    	std::unique_ptr<TFrLogin> FrLogin;
		std::unique_ptr<TFrRegister> FrRegister;
		AuthenticationService *authenticationService;

    public:		// User declarations
        __fastcall TFAuthentication(TComponent* Owner);
       	__fastcall TFAuthentication(TComponent* Owner, AuthenticationService *_authenticationService, TDataModule1 *dataModule);
        void __fastcall FrLoginRegisterSelect(TObject *Sender);
      	void __fastcall FrLoginSignInComplete(TObject *Sender, TModalResult result);

        void __fastcall FrRegisterSignInSelect(TObject *Sender);
        void __fastcall FrRegisterRegisterComplete(TObject *Sender, TModalResult result);

        virtual void __fastcall CreateParams(TCreateParams &Params);

};
//---------------------------------------------------------------------------
extern PACKAGE TFAuthentication *FAuthentication;
//---------------------------------------------------------------------------
#endif
