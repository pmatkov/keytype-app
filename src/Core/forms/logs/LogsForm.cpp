//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogsForm.h"
#include "UIUtils.h"
#include "FileUtils.h"
#include "CryptoUtils.h"
#include "Logger.h"
#include "EDirNotFoundException.h"
#include "ENullPointerException.h"

#include <vector>
#include <optional>

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

void TFLogs::updateLogBrowser(int index) {

    // read log file

	std::optional<std::vector<UnicodeString>> encryptedLogEntries = FileUtils::readFromTextFileByLine(FileUtils::createProjectSubDirPath("Log") + LVLogFiles->Selected->Caption);

	MLogs->Clear();
	MLogs->Lines->BeginUpdate();

    if (encryptedLogEntries.has_value()) {

        for (const UnicodeString &encryptedEntry: *encryptedLogEntries) {

            // decrpyt log entries

           UnicodeString decryptedEntry = CryptoUtils::decryptStringAES(encryptedEntry);
           MLogs->Lines->Add(decryptedEntry);
         }
    }

    MLogs->Lines->EndUpdate();
}

void __fastcall TFLogs::LVLogFilesSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
	if (LVLogFiles->Selected) {
    	updateLogBrowser(LVLogFiles->ItemIndex);
    }
}

void __fastcall TFLogs::LVLogFilesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{

	if (LVLogFiles->SelCount > 1) {

		TItemStates selected = TItemStates() << isSelected;
		TListItem *Item = LVLogFiles->GetNextItem(Item, sdAll, selected);

		while (Item) {
			Item->Selected = false;
			Item = LVLogFiles->GetNextItem(Item, sdAll, selected);
		}
	}
	else if (!LVLogFiles->SelCount) {

		if (LVLogFiles->ItemFocused) {
           LVLogFiles->ItemFocused->Focused = false;
		}
        MLogs->Clear();
	}
}

void __fastcall TFLogs::FormActivate(TObject *Sender)
{

    // get list of log files

	std::optional<std::vector<UnicodeString>> logs;
	UnicodeString dirPath = FileUtils::createProjectSubDirPath("Log");

    try {
        logs = FileUtils::getFiles(dirPath, "log");
    } catch (CustomExceptions::EDirNotFoundException &ex) {
         throw Exception("Log dir not found");
    }

    if (logs.has_value()) {

        std::vector<UnicodeString> logDetails;

		for (const UnicodeString &log: *logs) {

			UnicodeString path = FileUtils::createProjectSubDirPath("Log") + log;

			UnicodeString fileAge = FileUtils::getFileAge(path);
			UnicodeString fileSize = FileUtils::getFileSize(path);

            logDetails.insert(logDetails.end(), {log, fileAge, fileSize});
		}

    	UIUtils::setListViewItems(LVLogFiles, logDetails, 3);
    }
    else {
    	LOGGER(LogLevel::Info, "No logs found");
    }

}

//---------------------------------------------------------------------------

