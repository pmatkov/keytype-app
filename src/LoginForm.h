//---------------------------------------------------------------------------

#ifndef LoginFormH
#define LoginFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <memory>

#include "MainSession.h"
#include "AuthenticationService.h"

//---------------------------------------------------------------------------
class TFLogin : public TForm
{
    __published:	// IDE-managed Components
        TLabel *LUsername;
        TLabel *LPassword;
        TEdit *EUsername;
        TEdit *EPassword;
        TButton *BtLogin;
        TButton *BtGuest;
        void __fastcall BtGuestClick(TObject *Sender);

    private:	// User declarations
		AuthenticationService *authenticationService;

    public:		// User declarations
        __fastcall TFLogin(TComponent* Owner);
       	__fastcall TFLogin(TComponent* Owner, AuthenticationService *_authenticationService);

};
//---------------------------------------------------------------------------
extern PACKAGE TFLogin *FLogin;
//---------------------------------------------------------------------------
#endif
