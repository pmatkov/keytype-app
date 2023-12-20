//---------------------------------------------------------------------------

#include <vcl.h>

#include "GeneratedTextFrame.h"
#include "PracticeForm.h"
#include "UIUtils.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "DcWord.h"

#define LETTERS 26
#define BUTTON_SIZE 18

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrGeneratedText *FrGeneratedText;

//---------------------------------------------------------------------------
__fastcall TFrGeneratedText::TFrGeneratedText(TComponent* Owner) : TFrame(Owner) {

    setGroupBoxState(RGGeneratedText, GBCharacters, GBWords);

    createTBButtons(TBLetters, LETTERS);
    SendMessage(TBLetters->Handle, TB_SETBUTTONWIDTH, 0, MAKELPARAM(BUTTON_SIZE, BUTTON_SIZE));

    loadWordLists("WordList", CBTextFiles, LVWords, wordListCollection);

    setComboBoxItems(CBCategory, DcWord::getWordCategoriesAsStrings(), -1);

    DFileOpen->InitialDir = FileUtils::getAbsolutePath("WordList", false);
    dictionary.parseJsonToDictionary(FileUtils::getAbsolutePath("Data\\dictionary.json", true));

}

 __fastcall TFrGeneratedText::~TFrGeneratedText() {

    deleteTBButtons(buttons);
 }

 void TFrGeneratedText::displayTimedMessage(TTimer *timer, TLabel *label, const UnicodeString &msg) {
    label->Font->Color = clBlue;
    label->Caption = msg;
    timer->Enabled = true;

}


void TFrGeneratedText::createTBButtons(TToolBar* toolbar, int count) {

	for (int i = 0; i < count; i++) {

		buttons.push_back(new TToolButton(toolbar));

        buttons[i]->Parent = TBLetters;
        buttons[i]->AutoSize = false;
        buttons[i]->Caption = Char('Z' - i);
        buttons[i]->Style = tbsCheck;

        if (i % (count/ 2) == 0) {
            buttons[i]->Wrap = true;
        }
    }
}

 void TFrGeneratedText::deleteTBButtons(std::vector<TToolButton*> buttons) {

 	for (int i = 0; i < buttons.size(); i++)  {
    	delete buttons[i];
    }
 }

   void TFrGeneratedText::loadWordLists(const UnicodeString &path, TComboBox *comboBox, TListView *listview, std::vector<WordList> &wordListCollection) {

 	UnicodeString dirPath = FileUtils::getAbsolutePath(path, false);
    std::optional<std::vector<UnicodeString>> filenames = FileUtils::getFileNames(dirPath);

    if (filenames.has_value()) {

        for (const UnicodeString &fname : *filenames) {

        	std::optional<std::vector<UnicodeString>> wordlist = WordList::parseTextToWordList(dirPath + fname);

            if (wordlist.has_value()) {

                wordListCollection.push_back(WordList(fname, *wordlist));
            }
        }
        setComboBoxItems(comboBox, *filenames, 0);
        setListViewItems(listview, wordListCollection[comboBox->ItemIndex].getWordList());
    }

 }


 void  TFrGeneratedText::setComboBoxItems(TComboBox *comboBox, const std::vector<UnicodeString> &items, int defaultIndex) {

    comboBox->Items->Clear();

    for (const UnicodeString &item : items) {
        comboBox->Items->Add(item);
    }

    comboBox->ItemIndex = defaultIndex;
 }

 void TFrGeneratedText::setListViewItems(TListView *listview, const std::vector<UnicodeString> &items) {

 	listview->Items->Clear();

    listview->Items->BeginUpdate();

    for (const UnicodeString &item : items) {

        TListItem *listItem = listview->Items->Add();
        listItem->Caption = item;
    }
    listview->Items->EndUpdate();
}


 void TFrGeneratedText::setGroupBoxState(TRadioGroup* radioGroup, TGroupBox *primary, TGroupBox *secondary) {
    if (radioGroup->ItemIndex == 0) {

    	UIUtils::switchActiveControl(primary, secondary);
        UIUtils::disableChildControls(secondary);
        UIUtils::enableChildControls(primary);

    } else {

      	UIUtils::switchActiveControl(secondary, primary);
        UIUtils::disableChildControls(primary);
        UIUtils::enableChildControls(secondary);
    }
}


void __fastcall TFrGeneratedText::RGGeneratedTextClick(TObject *Sender)
{
	setGroupBoxState(RGGeneratedText, GBCharacters, GBWords);
}


void __fastcall TFrGeneratedText::BtBrowseClick(TObject *Sender) {
	if (DFileOpen->Execute()) {

		 if (FileExists(DFileOpen->FileName)) {

             UnicodeString path = DFileOpen->FileName;
             UnicodeString fname = ExtractFileName(path);

             if (CBTextFiles->Items->IndexOf(fname) == -1) {

                CBTextFiles->Items->Add(fname);
                CBTextFiles->ItemIndex = CBTextFiles->Items->Count - 1;

                std::optional<std::vector<UnicodeString>> wordlist = WordList::parseTextToWordList(path);

                if (wordlist.has_value()) {
                    wordListCollection.push_back(WordList(fname, *wordlist));
                }

                setListViewItems(LVWords, wordListCollection[CBTextFiles->ItemIndex].getWordList());

             }
		 }
	}
}


 const std::vector<TToolButton*>& TFrGeneratedText::getButtons() const {
	return buttons;
}


void __fastcall TFrGeneratedText::CBSelectAllClick(TObject *Sender)
{
	for (TToolButton *button : buttons) {
		button->Down = CBSelectAll->Checked ? true : false;
	}
}


void __fastcall TFrGeneratedText::LVWordsSelectItem(TObject *Sender, TListItem *Item, bool Selected) {

	if (LVWords->Selected) {

		EWord->Text = LVWords->Selected->Caption;

        std::optional<DcWord> word = dictionary.getWord(LVWords->Selected->Caption);

		if (word.has_value()) {

			int index = CBCategory->Items->IndexOf(DcWord::wordCategoryToString((*word).getWordCategory()));

			if (index != -1) {

				CBCategory->ItemIndex = index;
			}

			EDefinition->Text = (*word).getDefinition();
			ESynonyms->Text = (*word).getSynonymsAsString();
		}
		else {
			resetFrameFields(false);

		}

	}

}

void __fastcall TFrGeneratedText::LVWordsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
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
        resetFrameFields(true);
	}
}

void TFrGeneratedText::resetFrameFields(bool all) {
    if (all) {
    	BtAddSave1->Caption = "Add";
        BtDelete1->Enabled = false;
       	EWord->Text = "";
    }

	CBCategory->ItemIndex = -1;
	EDefinition->Text = "";
	ESynonyms->Text = "";
}


bool TFrGeneratedText::fieldsAreEmpty() {
   return (EWord->Text.IsEmpty() || EDefinition->Text.IsEmpty() || ESynonyms->Text.IsEmpty() || CBCategory->ItemIndex == -1);
}


void __fastcall TFrGeneratedText::BtDelete1Click(TObject *Sender) {
    std::vector<UnicodeString> wordlist = wordListCollection[CBTextFiles->ItemIndex].getWordList();
    wordlist.erase(std::remove(wordlist.begin(), wordlist.end(), EWord->Text), wordlist.end());
    wordListCollection[CBTextFiles->ItemIndex].setWordList(wordlist);

    UnicodeString filepath = FileUtils::getAbsolutePath("WordList\\" + wordListCollection[CBTextFiles->ItemIndex].getWordListName(), true);
    FileUtils::saveToTextFile(filepath, wordlist);

    dictionary.deleteWord(LVWords->Selected->Caption);

    std::optional<UnicodeString> json = Dictionary::generateJsonFromDictionary(dictionary.getDictionary());

    if (json.has_value()) {
        FileUtils::saveToJsonFile(FileUtils::getAbsolutePath("Data\\dictionary.json", true), *json);
    }

    setListViewItems(LVWords, wordListCollection[CBTextFiles->ItemIndex].getWordList());
    resetFrameFields(true);

    displayTimedMessage(msgDisplayTimer, LInfo, "Deleted");
}


void __fastcall TFrGeneratedText::BtAddSave1Click(TObject *Sender) {
	if (fieldsAreEmpty()) {
     	ShowMessage("Input fields should not be empty.");
        return;
     }

    std::vector<UnicodeString> wordlist = wordListCollection[CBTextFiles->ItemIndex].getWordList();
    int index = TextUtils::findString(wordlist, EWord->Text);
    bool newWord = index == -1 ? true : false;

    if (BtAddSave1->Caption.Compare("Add") == 0) {
        if (!newWord) {
            ShowMessage("Word is already in the list.");
            return;
        }
    }
    else {

    	DcWord word;
    	if (dictionary.getWord(LVWords->Selected->Caption).has_value()) {
		   word = *(dictionary.getWord(LVWords->Selected->Caption));
        }

        if (EWord->Text.Compare(word.getWord()) == 0  && CBCategory->Text.Compare(DcWord::wordCategoryToString(word.getWordCategory())) == 0 && EDefinition->Text.Compare(word.getDefinition()) == 0 \
            && TextUtils::splitTextIntoWords(ESynonyms->Text) == word.getSynonyms()) {
            ShowMessage("Nothing to save.");
            return;
        };
     }

     if (newWord) {
     	wordlist.push_back(EWord->Text);
     	wordListCollection[CBTextFiles->ItemIndex].setWordList(wordlist);
        UnicodeString filepath = FileUtils::getAbsolutePath("WordList\\" + wordListCollection[CBTextFiles->ItemIndex].getWordListName(), true);
     	FileUtils::saveToTextFile(filepath, wordlist);
     }

     dictionary.setWord(EWord->Text, DcWord(EWord->Text, DcWord::stringToWordCategory(CBCategory->Text), EDefinition->Text, TextUtils::splitTextIntoWords(ESynonyms->Text)));

     std::optional<UnicodeString> json = Dictionary::generateJsonFromDictionary(dictionary.getDictionary());

    if (json.has_value()) {
        FileUtils::saveToJsonFile(FileUtils::getAbsolutePath("Data\\dictionary.json", true), *json);
    }

    setListViewItems(LVWords, wordListCollection[CBTextFiles->ItemIndex].getWordList());
    resetFrameFields(true);
    UnicodeString msg = BtAddSave1->Caption.Compare("Add") == 0 ? "Added" : "Saved";
    displayTimedMessage(msgDisplayTimer, LInfo, msg);

}


void __fastcall TFrGeneratedText::CBTextFilesChange(TObject *Sender) {

	setListViewItems(LVWords, wordListCollection[CBTextFiles->ItemIndex].getWordList());
    resetFrameFields(true);

}

void __fastcall TFrGeneratedText::msgDisplayTimerTimer(TObject *Sender) {
     msgDisplayTimer->Enabled = false;
     LInfo->Caption = "";
}

