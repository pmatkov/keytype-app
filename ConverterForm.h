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

#include "WordList.h"
#include "Dictionary.h"
#include <Vcl.ExtCtrls.hpp>
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
private:	// User declarations

public:		// User declarations
	__fastcall TFConverter(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFConverter *FConverter;
//---------------------------------------------------------------------------
#endif
