//---------------------------------------------------------------------------

#ifndef ConverterFormH
#define ConverterFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "DataModule.h"
#include <Vcl.ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------
class TFConverter : public TForm
{
__published:	// IDE-managed Components
	TButton *BtConvert;
	TLabel *LInput;
	TLabel *LOutput;
	TEdit *EInput;
	TEdit *EOutput;
	TButton *BtBrowse;
	TOpenTextFileDialog *DFileOpen;
	TLabel *LInfo;
	TTimer *msgDisplayTimer;
	void __fastcall BtBrowseClick(TObject *Sender);
	void __fastcall BtConvertClick(TObject *Sender);
	void __fastcall msgDisplayTimerTimer(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);

private:	// User declarations
	TDataModule1 *dataModule;

public:		// User declarations
	__fastcall TFConverter(TComponent* Owner);
    __fastcall TFConverter(TComponent* Owner, TDataModule1 *_dataModule);
};
//---------------------------------------------------------------------------
extern PACKAGE TFConverter *FConverter;
//---------------------------------------------------------------------------
#endif
