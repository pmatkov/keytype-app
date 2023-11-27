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

	for (int i = 0; i < LETTERS; i++) {

		buttons.push_back(new TToolButton(TBLetters));

		buttons[i]->Parent = TBLetters;
		buttons[i]->AutoSize = false;
		buttons[i]->Caption = Char('Z' - i);
		buttons[i]->Style = tbsCheck;

		if (i % (LETTERS/ 2) == 0) {
			buttons[i]->Wrap = true;
		}
	}
	SendMessage(TBLetters->Handle, TB_SETBUTTONWIDTH, 0, MAKELPARAM(18, 18));

	RGGeneratedText->ItemIndex = 0;
	updateGroupBoxState();

	// stavit u FormShow?
	dictionary.parseJsontoWordInfo("Data\\dictionary.json");

	BtDelete1->Enabled = false;
	listChanged = false;

	_di_IXMLlibraryType library = Getlibrary(XMLDocument1);

	for (int i = 0; i < library->Count; i++) {

		_di_IXMLcategoryType bookCategory = library->category[i];

		for (int j = 0; j < bookCategory->Count; j++) {

			_di_IXMLgenreType bookGenre =  bookCategory->genre[j];

			for (int k = 0; k < bookGenre->Count; k++) {

				mapOfBooks[bookGenre->Get_name()].push_back(bookGenre->book[k]);

			}

		}
	}

}

__fastcall TFPractice::~TFPractice() {

	  for (int i = 0; i < LETTERS; i++)  {
		  delete buttons[i];
	  }

}

void TFPractice::setSessionModule(SessionModule *_sessionModule) {

	if (_sessionModule) {
	   sessionModule = _sessionModule;
	}

}


const std::vector<TToolButton*>& TFPractice::getButtons() const {
	return buttons;
}


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

// konstruktor?
void __fastcall TFPractice::FormShow(TObject *Sender)
{
	// obrisati?
//	CBTextFiles->Items->Add("");

	UnicodeString path = FileUtils::createAbsolutePath(DIR_NAME, false);

	std::optional<std::vector<UnicodeString>> fileNames = FileUtils::getFileNamesInDir(path);

	if (fileNames.has_value()) {

		CBTextFiles->Items->Clear();

		for (const UnicodeString &fname : *fileNames) {

			loadWordListFromFile(path + fname);
			CBTextFiles->Items->Add(fname);
		}

		CBTextFiles->ItemIndex = 0;
		cbTextFilesPrevIndex = CBTextFiles->ItemIndex;
    }

	loadListViewItems();

	int count = static_cast<int> (WordCategory::Count);

	for (int i = 0; i < count; i++) {
		 CBCategory->Items->Add(WordInfo::wordCategoryToString(static_cast<WordCategory>(i)));
	}

	CBCategory->ItemIndex = -1;

	DFileOpen->InitialDir = path;
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

void TFPractice::loadWordListFromFile(const UnicodeString &path) {

	std::optional<UnicodeString> fileContents = FileUtils::readFromTextFile(path);

	if (fileContents.has_value()) {

		std::vector<UnicodeString> wordList;

		if (TextUtils::countWords(*fileContents) > 1) {

			std::vector<UnicodeString> words = TextUtils::splitTextIntoWords(*fileContents);
			wordList.insert(wordList.end(), words.begin(), words.end());

		}
		else {
			wordList.push_back(*fileContents);
		}

		UnicodeString filename = ExtractFileName(path);

		wordListCollection.push_back(WordList(filename, wordList));

	}
}


//---------------------------------------------------------------------------
void TFPractice::loadListViewItems() {

	if (LVWords->Items->Count) {
		LVWords->Items->Clear();
	}

	if (CBTextFiles->ItemIndex != -1) {


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

		BtAddSave1->Caption = "Save";
		BtDelete1->Enabled = true;
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
		BtAddSave1->Caption = "Add";
		BtDelete1->Enabled = false;
	}

}
//---------------------------------------------------------------------------

void __fastcall TFPractice::BtDelete1Click(TObject *Sender)
{
	 dictionary.deleteWordInfo(LVWords->Selected->Caption);

	 listChanged = true;
}
//---------------------------------------------------------------------------

void __fastcall TFPractice::BtAddSave1Click(TObject *Sender)
{
	 if (BtAddSave1->Caption.Compare("Add") == 0) {

		 if (!EWord->Text.IsEmpty() && !EDefinition->Text.IsEmpty() && !ESynonyms->Text.IsEmpty() && CBCategory->ItemIndex != -1) {

			dictionary.setWordInfo(EWord->Text, WordInfo(EWord->Text, WordInfo::stringToWordCategory(CBCategory->Text), EDefinition->Text, TextUtils::splitTextIntoWords(ESynonyms->Text)));

		 }
		 else {
			 ShowMessage("Fields are empty");
		 }
	 }
	 else if (BtAddSave1->Caption.Compare("Save") == 0 && wordInDictionary) {

		WordInfo wordinfo = *(dictionary.getWordInfo(LVWords->Selected->Caption));

		if (EWord->Text.Compare(wordinfo.getWord()) == 0 && CBCategory->Text.Compare(WordInfo::wordCategoryToString(wordinfo.getWordCategory())) == 0 && EDefinition->Text.Compare(wordinfo.getDefinition()) == 0 \
			&& TextUtils::splitTextIntoWords(ESynonyms->Text) == wordinfo.getSynonyms()) {

			ShowMessage("Nothing was changed");
		}
		else if (!EWord->Text.IsEmpty() && !EDefinition->Text.IsEmpty() && !ESynonyms->Text.IsEmpty() && CBCategory->ItemIndex != -1) {
			  ShowMessage("Fields are empty");
		}
		else {
			dictionary.setWordInfo(LVWords->Selected->Caption, WordInfo(EWord->Text, WordInfo::stringToWordCategory(CBCategory->Text), EDefinition->Text, TextUtils::splitTextIntoWords(ESynonyms->Text)));
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

		FileUtils::saveToJsonFile("Data\\dictionary2.json", *strOptional);
	}
  }
}
//---------------------------------------------------------------------------


void __fastcall TFPractice::TVLiteratureCategoriesChange(TObject *Sender, TTreeNode *Node)
{

	if (Node) {

		updateListView(Node);
	}
}
//---------------------------------------------------------------------------

void TFPractice::updateListView(TTreeNode* selectedNode)
{
	LVLiteratureDetails->Items->Clear();
	MParagraph->Clear();

	if (selectedNode->Parent) {

		UnicodeString genre = selectedNode->Text.LowerCase();

		std::map<UnicodeString, std::vector<_di_IXMLbookType>>::iterator it = mapOfBooks.find(genre);

		if (it != mapOfBooks.end()) {

			std::vector<_di_IXMLbookType> books = it->second;

			for (const _di_IXMLbookType& book : books)
			{
				TListItem* item = LVLiteratureDetails->Items->Add();
				item->Caption = book->Get_author();
				item->SubItems->Add(book->Get_title());
				item->SubItems->Add(IntToStr(book->Get_year()));

				MParagraph->Lines->Add(book->Get_paragraph());
			}

		}

	}
}

