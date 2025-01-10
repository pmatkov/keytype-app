//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConverterForm.h"
#include "UIUtils.h"
#include "TextUtils.h"
#include "FileUtils.h"
#include "EFileNotFoundException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFConverter *FConverter;
//---------------------------------------------------------------------------
__fastcall TFConverter::TFConverter(TComponent* Owner) 	: TForm(Owner)  {}

__fastcall TFConverter::TFConverter(TComponent* Owner, TDataModule1 *_dataModule) : TForm(Owner)  {

    if (_dataModule) {
    	dataModule = _dataModule;
    }
}

void __fastcall TFConverter::FormActivate(TObject *Sender)
{
   EInput->Text = "";
   EOutput->Text = "";
}

void __fastcall TFConverter::BtBrowseClick(TObject *Sender)
{

    // select word list file

    UIUtils::setFileDialogProperties(DFileOpen, "WordList", "txt");

    if (DFileOpen->Execute()) {

		 if (FileExists(DFileOpen->FileName)) {

             UnicodeString path = DFileOpen->FileName;
             UnicodeString filename = ExtractFileName(path);

             EInput->Text = filename;
             EOutput->Text = filename.Delete(filename.Length()-2, 3) + "json";
		 }
	}
}

void __fastcall TFConverter::BtConvertClick(TObject *Sender)
{

    if (dataModule->convertWordList(DFileOpen->FileName)) {
          UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Converted");
    }
    else {
        UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Failed");
    }
}

void __fastcall TFConverter::msgDisplayTimerTimer(TObject *Sender)
{
	UIUtils::removeTimedMessage(msgDisplayTimer, LInfo);
}

