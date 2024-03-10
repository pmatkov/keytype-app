//---------------------------------------------------------------------------

#ifndef PracticeOptionsFormH
#define PracticeOptionsFormH

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
#include <vcl.h>
#include <memory>

#include "Dictionary.h"
#include "MainSession.h"

#include "GeneratedTextFrame.h"
#include "ExternalSourcesFrame.h"
#include "CustomTextFrame.h"

//---------------------------------------------------------------------------
class TFPracticeOptions : public TForm
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

	MainSession  *mainSession;

public:		// User declarations
	__fastcall TFPracticeOptions(TComponent* Owner);
    __fastcall TFPracticeOptions(TComponent* Owner, MainSession *mainSession);

    TFrGeneratedText* GetFrGeneratedText() const;
    TFrExternalSources* GetFrExternalSources() const;
    TFrCustomText* GetFrCustomText() const;


//    void setMainSession(MainSession *_mainSession);
//    MainSession * getMainSession();

};

//---------------------------------------------------------------------------
extern PACKAGE TFPracticeOptions *FPracticeOptions;
//---------------------------------------------------------------------------

#endif
