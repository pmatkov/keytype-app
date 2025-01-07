//---------------------------------------------------------------------------

#ifndef PracticeSourceFormH
#define PracticeSourceFormH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.AppEvnts.hpp>

#include <memory>

#include "DataModule.h"
#include "Dictionary.h"
#include "MainSession.h"

#include "AuthenticationService.h"
#include "GeneratedTextFrame.h"
#include "ExternalSourcesFrame.h"
#include "CustomTextFrame.h"

//---------------------------------------------------------------------------
class TFPracticeSource : public TForm
{
__published:	// IDE-managed Components
	TButton *BtAccept;
	TButton *BtCancel;
	TPageControl *PCSourceText;
	TTabSheet *TSGeneratedText;
	TTabSheet *TSExternalSources;
	TTabSheet *TSCustomText;

private:	// User declarations
	std::unique_ptr<TFrGeneratedText> FrGeneratedText;
	std::unique_ptr<TFrExternalSources> FrExternalSources;
	std::unique_ptr<TFrCustomText> FrCustomText;

    TDataModule1 *dataModule;
	MainSession  *mainSession;
    AuthenticationService *authService;

public:		// User declarations
	__fastcall TFPracticeSource(TComponent* Owner);
    __fastcall TFPracticeSource(TComponent* Owner, TDataModule1 *_dataModule, MainSession *mainSession, AuthenticationService *_authService);

    TFrGeneratedText* GetFrGeneratedText() const;
    TFrExternalSources* GetFrExternalSources() const;
    TFrCustomText* GetFrCustomText() const;

};

//---------------------------------------------------------------------------
extern PACKAGE TFPracticeSource *FPracticeSource;
//---------------------------------------------------------------------------

#endif
