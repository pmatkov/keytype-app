//---------------------------------------------------------------------------

#include <vcl.h>
#include "PracticeForm.h"
#include "WordList.h"
#include "FileUtils.h"

#define LETTERS 26
#define PATH "WordList\\"

#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

TFPractice *FPractice;
//---------------------------------------------------------------------------
__fastcall TFPractice::TFPractice(TComponent* Owner) : TForm(Owner) {

	// letters toolbar

	LettersToolbar->ShowCaptions = true;

	for (int i = 0; i < LETTERS; i++) {

//		buttons.push_back(std::make_unique<TToolButton>(LettersToolbar));

		buttons.push_back(new TToolButton(LettersToolbar));
		buttons[i]->Parent = LettersToolbar;
		buttons[i]->Caption = Char('Z' - i);
		buttons[i]->Style = tbsCheck;
		buttons[i]->Width =  LettersToolbar->ButtonWidth / LETTERS/ 2;

		if (i == LETTERS/ 2) {
			buttons[i]->Wrap = true;
		}
	}

	RGGeneratedText->ItemIndex = 0;
	updateGroupBoxState();

}

__fastcall TFPractice::~TFPractice() {
	  for (int i = 0; i < LETTERS; i++)  {
		  delete buttons[i];
      }
}

//const std::vector<std::unique_ptr<TToolButton>>& TFPractice::getButtons() const {
//	return buttons;
//}


const std::vector<TToolButton*>& TFPractice::getButtons() const {
	return buttons;
}


void __fastcall TFPractice::BCancelButtonClick(TObject *Sender)
{
	  ModalResult = mrCancel;
}

void __fastcall TFPractice::updateGroupBoxState()
{
	if (RGGeneratedText->ItemIndex == 0) {

		GBCharacters->Enabled = true;
		GBWords->Enabled = false;

		changeChildControlsStatus(GBCharacters, true);
		changeChildControlsStatus(GBWords, false);

	} else {
		GBWords->Enabled = true;
		GBCharacters->Enabled = false;

		changeChildControlsStatus(GBWords, true);
		changeChildControlsStatus(GBCharacters, false);
	}
}



void TFPractice::changeChildControlsStatus(TWinControl* parentControl, Boolean status)
{
	for (int i = 0; i < parentControl->ControlCount; i++)
	{
        TControl* childControl = parentControl->Controls[i];
		childControl->Enabled = status;
	}
}

void __fastcall TFPractice::RGGeneratedTextClick(TObject *Sender)
{
	updateGroupBoxState();
}

void __fastcall TFPractice::CBSelectAllClick(TObject *Sender)
{
		for (TToolButton *button : buttons) {
		button->Down = CBSelectAll->Checked ? true : false;

	}
}


void __fastcall TFPractice::FormShow(TObject *Sender)
{
	CBTextFiles->Items->Add("");

	UnicodeString path = FileUtils::createFilePath(PATH);

	if (TDirectory::Exists(path)) {
		TSearchRec searchRec;

		if (FindFirst(path + "\\*.txt", faAnyFile, searchRec) == 0) {

			CBTextFiles->Items->Clear();
			do {
				CBTextFiles->Items->Add(searchRec.Name);
			} while (FindNext(searchRec) == 0);

			FindClose(searchRec);

			CBTextFiles->ItemIndex = 0;
		}
	}

	DFileOpen->InitialDir = path;

	loadListViewItems();

}

void __fastcall TFPractice::BBrowseButtonClick(TObject *Sender)
{

	if (DFileOpen->Execute()) {

		 if (FileExists(DFileOpen->FileName)) {

			UnicodeString filename = ExtractFileName(DFileOpen->FileName);

			int index = CBTextFiles->Items->IndexOf(filename);

			if (index == -1) {
				  CBTextFiles->Items->Add(filename);
				  CBTextFiles->ItemIndex = CBTextFiles->Items->Count - 1;
			}

		 }

	}

}


void __fastcall TFPractice::CBTextFilesSelect(TObject *Sender)
{
		loadListViewItems();
}

void TFPractice::loadListViewItems() {

	if (LVWords->Items->Count > 0) {
		LVWords->Items->Clear();
	}

	if (CBTextFiles->ItemIndex != -1) {

		UnicodeString path = FileUtils::createFilePath(PATH);

		path = path + CBTextFiles->Items->Strings[CBTextFiles->ItemIndex];

		if (FileExists(path))  {

			TFileStream *fileStream = new TFileStream(path, fmOpenRead);

			try
			{
				TStreamReader *streamReader = new TStreamReader(fileStream);
				try
				{

					while (!streamReader->EndOfStream) {

						TListItem * item = LVWords->Items->Add();
						item->Caption = streamReader->ReadLine();

					}

				}
				__finally
				{
					delete streamReader;
				}
			}
			__finally
			{
				delete fileStream;
			}

		}

	}

}
//---------------------------------------------------------------------------

