//---------------------------------------------------------------------------

#include "PracticeForm.h"
#include "TextUtils.h"
#include "FileUtils.h"
#include "WordInfo.h"
#include "EFileSizeExceededException.h"

#define DIR_NAME "WordList"
#define LETTERS 26

#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

TFPractice *FPractice;
//---------------------------------------------------------------------------
__fastcall TFPractice::TFPractice(TComponent* Owner) : TForm(Owner) {


	TBLetters->ShowCaptions = true;

	for (int i = 0; i < LETTERS; i++) {

//		buttons.push_back(std::make_unique<TToolButton>(TBLetters));

		buttons.push_back(new TToolButton(TBLetters));
		buttons[i]->Parent = TBLetters;
		buttons[i]->Caption = Char('Z' - i);
		buttons[i]->Style = tbsCheck;
		buttons[i]->Width =  TBLetters->ButtonWidth / LETTERS/ 2;

		if (i == LETTERS/ 2) {
			buttons[i]->Wrap = true;
		}
	}

	RGGeneratedText->ItemIndex = 0;
	updateGroupBoxState();

	// stavit u FormShow?
	dictionary.parseJsontoWordInfo("Data\\dictionary.json");

	BtDelete->Enabled = false;
	listChanged = false;

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


//void __fastcall TFPractice::BtCancelClick(TObject *Sender)
//{
//	  ModalResult = mrCancel;
//}

void TFPractice::updateGroupBoxState()
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
	for (int i = 0; i < parentControl->ControlCount; i++) {

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

// prebaciti u FileUtils - vraca sadrzaj direktorija *.txt
void __fastcall TFPractice::FormShow(TObject *Sender)
{
	CBTextFiles->Items->Add("");

	UnicodeString path = FileUtils::createAbsolutePath(DIR_NAME, false);

	if (TDirectory::Exists(path)) {

		TSearchRec searchRec;

		if (FindFirst(path + "*.txt", faAnyFile, searchRec) == 0) {

			CBTextFiles->Items->Clear();

			std::vector<UnicodeString> filenames;

			do {
				UnicodeString filename = searchRec.Name;

				try {
					FileUtils::checkFileSize(path + filename);
					filenames.push_back(filename);
					CBTextFiles->Items->Add(filename);
				}
				catch (EFileSizeExceededException &ex) {
					continue;
				}

			} while (FindNext(searchRec) == 0);

			FindClose(searchRec);

			for (const UnicodeString &fname : filenames) {
				loadWordListFromFile(path + fname);
			}

			CBTextFiles->ItemIndex = 0;
		}
	}

	DFileOpen->InitialDir = path;
	cbTextFilesPrevIndex = CBTextFiles->ItemIndex;

	loadListViewItems();

	int count = static_cast<int> (WordCategory::Count);

	for (int i = 0; i < count; i++) {
		 CBCategory->Items->Add(WordInfo::wordCategoryToString(static_cast<WordCategory>(i)));
	}

	CBCategory->ItemIndex = -1;
}

void __fastcall TFPractice::BtBrowseClick(TObject *Sender)
{

	if (DFileOpen->Execute()) {

		 if (FileExists(DFileOpen->FileName)) {

			try {
				FileUtils::checkFileSize(DFileOpen->FileName);

				UnicodeString filename = ExtractFileName(DFileOpen->FileName);

				int index = CBTextFiles->Items->IndexOf(filename);

				if (index == -1) {
					  CBTextFiles->Items->Add(filename);
					  CBTextFiles->ItemIndex = CBTextFiles->Items->Count - 1;

					  loadWordListFromFile(DFileOpen->FileName);
					  loadListViewItems();
				}

			}
			catch (EFileSizeExceededException &ex) {
				ex.displayMessage();
			}

		 }
	}
}


// prebaciti u WordList backend dio
void TFPractice::loadWordListFromFile(const UnicodeString &path) {

	if (FileExists(path))  {

		TFileStream *fileStream = new TFileStream(path, fmOpenRead);

		try
		{
			TStreamReader *streamReader = new TStreamReader(fileStream);

			try
			{
				std::vector<UnicodeString> wordList;

				while (!streamReader->EndOfStream) {


					UnicodeString line = streamReader->ReadLine();

					if (TextUtils::countWords(line) > 1) {

						std::vector<UnicodeString> words = TextUtils::splitLineIntoWords(line);
						wordList.insert(wordList.end(), words.begin(), words.end());

					}
					else {
						 wordList.push_back(line);
					}

				}

				UnicodeString filename = ExtractFileName(path);

				wordListCollection.push_back(WordList(filename, wordList));
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

//---------------------------------------------------------------------------
void TFPractice::loadListViewItems() {

	if (LVWords->Items->Count > 0) {
		LVWords->Items->Clear();
	}

	if (CBTextFiles->ItemIndex != -1 && CBTextFiles->ItemIndex < wordListCollection.size()) {


		if (wordListCollection[CBTextFiles->ItemIndex].getWordListName().Compare(CBTextFiles->Items->Strings[CBTextFiles->ItemIndex]) == 0) {

			LVWords->Items->BeginUpdate();

			for (const UnicodeString &word : wordListCollection[CBTextFiles->ItemIndex].getWordList()) {

				TListItem *item = LVWords->Items->Add();
				item->Caption = word;
			}

			LVWords->Items->EndUpdate();

		}

	}
}
 //---------------------------------------------------------------------------

void __fastcall TFPractice::CBTextFilesChange(TObject *Sender)
{
	if (cbTextFilesPrevIndex != CBTextFiles->ItemIndex) {
		cbTextFilesPrevIndex =	CBTextFiles->ItemIndex;
		loadListViewItems();
	}

}
//---------------------------------------------------------------------------

void TFPractice::clearInputFields() {
	EWord->Text = "";
	CBCategory->ItemIndex = -1;
	EDefinition->Text = "";
	EDefinition->Text = "";
	ESynonyms->Text = "";
}


//---------------------------------------------------------------------------

void __fastcall TFPractice::LVWordsSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{

	if (LVWords->Selected) {

		TListItem *selectedItem = LVWords->Selected;

		std::optional<WordInfo> wiOptional = dictionary.getWordInfo(selectedItem->Caption);

		if (wiOptional.has_value()) {

			wordInDictionary = true;

			WordInfo wordinfo = *wiOptional;

			EWord->Text = wordinfo.getWord();

			int i = CBCategory->Items->IndexOf(WordInfo::wordCategoryToString(wordinfo.getWordCategory()));

			if (i != -1) {

				CBCategory->ItemIndex = i;
			}

			EDefinition->Text = wordinfo.getDefinition();
			ESynonyms->Text = wordinfo.getSynonymsAsString();
		}
		else {
			wordInDictionary = false;
			clearInputFields();
		}

	}

}
//---------------------------------------------------------------------------

void __fastcall TFPractice::LVWordsChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
	if (LVWords->SelCount == 1) {

		BtAddSave->Caption = "Save";
		BtDelete->Enabled = true;
	}
	else if (LVWords->SelCount > 1) {

		TItemStates selected = TItemStates() << isSelected;
		TListItem *Item = LVWords->GetNextItem(Item, sdAll, selected);

		while (Item) {

			Item->Selected = false;
			Item = LVWords->GetNextItem(Item, sdAll, selected);
		}
	}
	else {

		if (LVWords->ItemFocused) {
           LVWords->ItemFocused->Focused = false;
		}

		if (wordInDictionary) {
			clearInputFields();
			wordInDictionary = false;
		}
		BtAddSave->Caption = "Add";
		BtDelete->Enabled = false;
	}

}
//---------------------------------------------------------------------------

void __fastcall TFPractice::BtDeleteClick(TObject *Sender)
{
	 dictionary.deleteWordInfo(LVWords->Selected->Caption);

	 listChanged = true;
}
//---------------------------------------------------------------------------

void __fastcall TFPractice::BtAddSaveClick(TObject *Sender)
{
	 if (BtAddSave->Caption.Compare("Add") == 0) {

		 if (!EWord->Text.IsEmpty() && !EDefinition->Text.IsEmpty() && !ESynonyms->Text.IsEmpty() && CBCategory->ItemIndex != -1) {
			dictionary.setWordInfo(EWord->Text, WordInfo(EWord->Text, WordInfo::stringToWordCategory(CBCategory->Text), EDefinition->Text, TextUtils::splitLineIntoWords(ESynonyms->Text)));

		 }
		 else {
			 ShowMessage("Fields are empty");
		 }
	 }
	 else if (BtAddSave->Caption.Compare("Save") == 0 && wordInDictionary) {

		WordInfo wordinfo = *(dictionary.getWordInfo(LVWords->Selected->Caption));

		if (EWord->Text.Compare(wordinfo.getWord()) == 0 && CBCategory->Text.Compare(WordInfo::wordCategoryToString(wordinfo.getWordCategory())) == 0 && EDefinition->Text.Compare(wordinfo.getDefinition()) == 0 \
			&& TextUtils::splitLineIntoWords(ESynonyms->Text) == wordinfo.getSynonyms()) {

			ShowMessage("Nothing was changed");
		}
		else if (!EWord->Text.IsEmpty() && !EDefinition->Text.IsEmpty() && !ESynonyms->Text.IsEmpty() && CBCategory->ItemIndex != -1) {
			  ShowMessage("Fields are empty");
		}
		else {
			dictionary.setWordInfo(LVWords->Selected->Caption, WordInfo(EWord->Text, WordInfo::stringToWordCategory(CBCategory->Text), EDefinition->Text, TextUtils::splitLineIntoWords(ESynonyms->Text)));
		}

	 }
	 listChanged = true;
}
//---------------------------------------------------------------------------

void __fastcall TFPractice::BtAcceptClick(TObject *Sender)
{
  if (listChanged) {

	std::optional<UnicodeString> strOptional = Dictionary::generateJsonFromWordInfo(dictionary.getWords());

	if (strOptional.has_value()) {

		FileUtils::saveJsonToFile("Data\\dictionary2.json", *strOptional);
	}
  }
}
//---------------------------------------------------------------------------

