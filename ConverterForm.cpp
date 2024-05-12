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


void __fastcall TFConverter::BtBrowseClick(TObject *Sender)
{

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
//    std::optional<UnicodeString> buffer;
//
//    try {
//        buffer = FileUtils::readFromTextFile(DFileOpen->FileName);
//    } catch (CustomExceptions::EFileNotFoundException &ex) {
//        LOGGER(LogLevel::Fatal, ex.getMessage());
//    }
//
//    if (buffer.has_value()) {
//    	std::vector<UnicodeString> wordList = TextUtils::splitToTokens(*buffer);
//    	std::optional<UnicodeString> jsonString = Dictionary::generateJsonFromWordList(wordList);
//
//    	if (jsonString.has_value()) {
//
//        	FileUtils::saveToTextFile(FileUtils::createAbsolutePath("Data\\" + EOutput->Text, true), std::vector<UnicodeString>{*jsonString});
//     	}
//    }

    if (dataModule->convertWordList(DFileOpen->FileName)) {
          UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Converted");
    }
    else {
        UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Failed");
    }


}
//---------------------------------------------------------------------------

void __fastcall TFConverter::msgDisplayTimerTimer(TObject *Sender)
{
	UIUtils::removeTimedMessage(msgDisplayTimer, LInfo);
}
//---------------------------------------------------------------------------

void __fastcall TFConverter::FormActivate(TObject *Sender)
{
   EInput->Text = "";
   EOutput->Text = "";
}
//---------------------------------------------------------------------------

