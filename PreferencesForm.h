//---------------------------------------------------------------------------

#ifndef PreferencesFormH
#define PreferencesFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "MainSession.h"
#include "AuthenticationService.h"
#include <Vcl.ExtCtrls.hpp>

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
	TCheckBox *CBConsecutiveMistakes;
	TCheckBox *CBSpeed;
	TLabel *LFont2;
	TLabel *LFontSize;
	TComboBox *CBFont2;
	TCheckBox *CBAccuracy;
	TComboBox *CBFontSize;
	TButton *BtReset2;
	TButton *BtCancel;
	TButton *BtReset1;
	TButton *BtAccept;
	TLabel *LSeparator;
	TComboBox *CBSeparator;
	TLabel *LArchiveLogLimit;
	TComboBox *CBArchiveLogLimit;
	TButton *BtArchiveLogs;
	TLabel *LArchiveStatus;
	TTimer *msgDisplayTimer;
	TLabel *LKeyboardLayout;
	TComboBox *CBKeyboardLayout;
	void __fastcall CBLanguageChange(TObject *Sender);
	void __fastcall CBLoggingEnableClick(TObject *Sender);
	void __fastcall BtReset1Click(TObject *Sender);
	void __fastcall BtReset2Click(TObject *Sender);
	void __fastcall BtAcceptClick(TObject *Sender);
	void __fastcall CBMistakeClick(TObject *Sender);
	void __fastcall CBConsecutiveMistakesClick(TObject *Sender);
	void __fastcall CBSpeedClick(TObject *Sender);
	void __fastcall CBAccuracyClick(TObject *Sender);
	void __fastcall CBCaretChange(TObject *Sender);
	void __fastcall CBSeparatorChange(TObject *Sender);
	void __fastcall CBFont2Change(TObject *Sender);
	void __fastcall CBFontSizeChange(TObject *Sender);
	void __fastcall CBLoggingChange(TObject *Sender);
	void __fastcall CBFont1Change(TObject *Sender);
	void __fastcall CBArchiveLogLimitChange(TObject *Sender);
	void __fastcall BtArchiveLogsClick(TObject *Sender);
	void __fastcall msgDisplayTimerTimer(TObject *Sender);
	void __fastcall CBKeyboardLayoutChange(TObject *Sender);
private:	// User declarations
	MainSession *mainSession;
    AuthenticationService *authService;

public:		// User declarations
	__fastcall TFPreferences(TComponent* Owner);
    __fastcall TFPreferences(TComponent* Owner, MainSession *_mainSession, AuthenticationService *_authService);
    void setAppSettingsItems();
    void setTypingSettingsItems();

};
//---------------------------------------------------------------------------
extern PACKAGE TFPreferences *FPreferences;
//---------------------------------------------------------------------------
#endif
