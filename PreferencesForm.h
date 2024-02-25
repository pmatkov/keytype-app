//---------------------------------------------------------------------------

#ifndef PreferencesFormH
#define PreferencesFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "MainSession.h"

//---------------------------------------------------------------------------
class TFPreferences : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TLabel *LLanguage;
	TComboBox *CBLanguage;
	TLabel *LLogging;
	TComboBox *CBLogging;
	TCheckBox *CBLoggingEnable;
	TLabel *LCaret;
	TComboBox *CBCaret;
	TCheckBox *CBMistake;
	TLabel *LFont1;
	TComboBox *CBFont1;
	TCheckBox *CBSeqMistakes;
	TCheckBox *CBSpeed;
	TLabel *LFont2;
	TLabel *LFontSize;
	TComboBox *CBFont2;
	TCheckBox *CBAccuracy;
	TComboBox *ComboBox1;
	TButton *BtReset2;
	TButton *BtCancel;
	TButton *BtReset1;
	TButton *BtAccept;
private:	// User declarations
	MainSession *mainSession;

public:		// User declarations
	__fastcall TFPreferences(TComponent* Owner);
    __fastcall TFPreferences(TComponent* Owner, MainSession *_mainSession);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPreferences *FPreferences;
//---------------------------------------------------------------------------
#endif
