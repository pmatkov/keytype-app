//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <optional>
#pragma hdrstop

#include "LogsForm.h"
#include "UIUtils.h"
#include "FileUtils.h"
#include "CryptoUtils.h"
#include "Logger.h"
#include "EDirNotFoundException.h"
#include "ENullPointerException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uTPLb_BaseNonVisualComponent"
#pragma link "uTPLb_Codec"
#pragma link "uTPLb_CryptographicLibrary"
#pragma link "uTPLb_Signatory"
#pragma resource "*.dfm"
TFLogs *FLogs;
//---------------------------------------------------------------------------
__fastcall TFLogs::TFLogs(TComponent* Owner) : TForm(Owner) {}

__fastcall TFLogs::TFLogs(TComponent* Owner, AuthenticationService *_authService, TDataModule1 *_dataModule) : TForm(Owner) {

    if (_authService && _dataModule) {

           authService = _authService;
           dataModule = _dataModule;

           LOGGER(LogLevel::Debug, "Created logs form");
	}
    else {
        throw CustomExceptions::ENullPointerException();
    }

}
//---------------------------------------------------------------------------
void __fastcall TFLogs::LVLogDatesSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
	if (LVLogDates->Selected) {
    	updateLogViewer(LVLogDates->ItemIndex);
    }
}


void TFLogs::updateLogViewer(int index) {

	MLogs->Clear();

    std::optional<std::vector<UnicodeString>> fileContents = FileUtils::readFromTextFileByLine(FileUtils::createAbsolutePath("Log", false) + LVLogDates->Selected->Caption);

	MLogs->Lines->BeginUpdate();

    if (fileContents.has_value()) {

        for (const UnicodeString &string: *fileContents) {
           MLogs->Lines->Add(string);
         }
    }

    MLogs->Lines->EndUpdate();
}

void __fastcall TFLogs::LVLogDatesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{

	if (LVLogDates->SelCount > 1) {

		TItemStates selected = TItemStates() << isSelected;
		TListItem *Item = LVLogDates->GetNextItem(Item, sdAll, selected);

		while (Item) {
			Item->Selected = false;
			Item = LVLogDates->GetNextItem(Item, sdAll, selected);
		}
	}
	else if (!LVLogDates->SelCount) {

		if (LVLogDates->ItemFocused) {
           LVLogDates->ItemFocused->Focused = false;
		}
        MLogs->Clear();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFLogs::FormActivate(TObject *Sender)
{
	std::optional<std::vector<UnicodeString>> fileNames;
   	UnicodeString dirPath = FileUtils::createAbsolutePath("Log", false);

    try {
        fileNames = FileUtils::getFileNames(dirPath, "log");
    } catch (CustomExceptions::EDirNotFoundException &ex) {
         throw Exception("Log dir not found");
    }

    if (fileNames.has_value()) {

        std::vector<UnicodeString> logInfos;

        for (const UnicodeString &fileName: *fileNames) {

        	UnicodeString fileAge = FileUtils::getFileAge(FileUtils::createAbsolutePath("Log", false) + fileName);
           	UnicodeString fileSize = FileUtils::getFileSize(FileUtils::createAbsolutePath("Log", false) + fileName);

            logInfos.insert(logInfos.end(), {fileName, fileAge, fileSize});
        }

    	UIUtils::setListViewItems(LVLogDates, logInfos, 3);
    }
    else {
    	LOGGER(LogLevel::Info, "No logs found");
    }

}

//---------------------------------------------------------------------------

