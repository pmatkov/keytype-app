//---------------------------------------------------------------------------

#ifndef PracticeFormH
#define PracticeFormH

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
#include "SessionModule.h"
#include "GeneratedTextFrame.h"
#include "ExternalSourcesFrame.h"
#include "CustomTextFrame.h"

//---------------------------------------------------------------------------
class TFPractice : public TForm
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

	SessionModule *sessionModule;

public:		// User declarations
	__fastcall TFPractice(TComponent* Owner);

    TFrGeneratedText* GetFrGeneratedText() const;
    TFrExternalSources* GetFrExternalSources() const;
    TFrCustomText* GetFrCustomText() const;

	void setSessionModule(SessionModule *_sessionModule);
    SessionModule* getSessionModule();

};

//---------------------------------------------------------------------------
extern PACKAGE TFPractice *FPractice;
//---------------------------------------------------------------------------

#endif
