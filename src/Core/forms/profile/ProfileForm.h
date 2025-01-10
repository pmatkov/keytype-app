//---------------------------------------------------------------------------

#ifndef ProfileFormH
#define ProfileFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "MainSession.h"
#include "AuthenticationService.h"
#include "DataModule.h"
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.Mask.hpp>

//---------------------------------------------------------------------------
class TFProfile : public TForm
{
__published:	// IDE-managed Components
	TLabel *LUsername;
	TLabel *LPassword;
	TLabel *LName;
	TLabel *LSurname;
	TLabel *LEmail;
	TLabel *LAge;
	TButton *BtEditSave;
	TButton *BtChangeImage;
	TGroupBox *GBProfile;
	TButton *BtDeleteImage;
	TDBImage *DBImage;
	TOpenPictureDialog *DFileOpen;
	TDBEdit *EUsername;
	TDBEdit *EName;
	TDBEdit *ESurname;
	TDBEdit *EEmail;
	TDBEdit *EAge;
	TLabel *LInfo;
	TTimer *msgDisplayTimer;
	TEdit *EPassword;

    void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtEditSaveClick(TObject *Sender);
	void __fastcall BtChangeImageClick(TObject *Sender);
	void __fastcall BtDeleteImageClick(TObject *Sender);
	void __fastcall BtDeleteClick(TObject *Sender);
	void __fastcall msgDisplayTimerTimer(TObject *Sender);
private:	// User declarations
 	MainSession *mainSession;
	AuthenticationService *authService;
    TDataModule1 *dataModule;
public:		// User declarations
	__fastcall TFProfile(TComponent* Owner);
    __fastcall TFProfile(TComponent* Owner,  MainSession *_mainSession, AuthenticationService *_authService, TDataModule1 *_dataModule);
};
//---------------------------------------------------------------------------
extern PACKAGE TFProfile *FProfile;
//---------------------------------------------------------------------------
#endif
