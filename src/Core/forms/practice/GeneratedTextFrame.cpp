//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.StrUtils.hpp>

#include "Factory.h"
#include "GeneratedTextFrame.h"
#include "PracticeForm.h"
#include "UIUtils.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "EnumUtils.h"
#include "Dictionary.h"
#include "DictionaryEntry.h"
#include "Generator.h"

#include "Logger.h"
#include "EDirNotFoundException.h"
#include "ENullPointerException.h"

#define LETTERS 26
#define BUTTON_SIZE 18

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TFrGeneratedText *FrGeneratedText;

//---------------------------------------------------------------------------
__fastcall TFrGeneratedText::TFrGeneratedText(TComponent* Owner) : TFrame(Owner), dictionary(ModelFactory::createDictionary(*this, *this)) {}

__fastcall TFrGeneratedText::TFrGeneratedText(TComponent* Owner, TDataModule1 *_dataModule) : TFrame(Owner), dictionary(ModelFactory::createDictionary(*this, *this)) {

	if (_dataModule) {
    	dataModule = _dataModule;

        UIUtils::setComboBoxItems(CBCharsWordMin, {"0", "3", "5", "7", "10"}, 0);
        UIUtils::setComboBoxItems(CBCharsWordMax, {"3", "5", "7", "10", UnicodeString(L'\u221E')}, 4);

        UIUtils::setComboBoxItems(CBWordsMin, {"5", "10", "15", "20", "25"}, 0);
        UIUtils::setComboBoxItems(CBWordsMax, {"5", "10", "15", "20", "25"}, 1);

        MPreview->Font->Color = clSilver;

        LOGGER(LogLevel::Debug, "Created generated text frame");

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFrGeneratedText::BtBrowseClick(TObject *Sender) {

  UIUtils::setFileDialogProperties(DFileOpen, "Data", "json");

	if (DFileOpen->Execute()) {

		 if (FileExists(DFileOpen->FileName)) {

             UnicodeString filename = ExtractFileName(DFileOpen->FileName);

             if (CBDictionaryFiles->Items->IndexOf(filename) == -1) {

                CBDictionaryFiles->Items->Add(filename);
                CBDictionaryFiles->ItemIndex = CBDictionaryFiles->Items->Count - 1;

                dictionary->setDictionary(filename);
             }
		 }
	}
}

void __fastcall TFrGeneratedText::LVDictionarySelectItem(TObject *Sender, TListItem *Item, bool Selected) {

	if (LVDictionary->Selected) {

        dictionary->getDictionaryEntry(LVDictionary->Selected->Caption);
	}
}

void __fastcall TFrGeneratedText::LVDictionaryMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {

	if (LVDictionary->SelCount == 1) {

		BtAddSave1->Caption = "Save";
		BtDelete1->Enabled = true;
	}
	else if (LVDictionary->SelCount > 1) {

		TItemStates selected = TItemStates() << isSelected;
		TListItem *Item = LVDictionary->GetNextItem(Item, sdAll, selected);

		while (Item) {
			Item->Selected = false;
			Item = LVDictionary->GetNextItem(Item, sdAll, selected);
		}
	}
	else {

		if (LVDictionary->ItemFocused) {
           LVDictionary->ItemFocused->Focused = false;
		}
        resetFrameFields();
	}
}

void TFrGeneratedText::resetFrameFields() {

    BtAddSave1->Caption = "Add";
    BtDelete1->Enabled = false;
    EWord->Text = "";

	CBCategory->ItemIndex = -1;
	EDefinition->Text = "";
	ESynonyms->Text = "";
}


bool TFrGeneratedText::areFieldsEmpty() {
   return (EWord->Text.IsEmpty() || EDefinition->Text.IsEmpty() || ESynonyms->Text.IsEmpty() || CBCategory->ItemIndex == -1);
}


void __fastcall TFrGeneratedText::BtDelete1Click(TObject *Sender) {

    if (LVDictionary->Selected) {
        dictionary->deleteDictionaryEntry(LVDictionary->Selected->Caption);
        resetFrameFields();

    	UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Deleted");
    }
}


void __fastcall TFrGeneratedText::BtAddSave1Click(TObject *Sender) {

	if (areFieldsEmpty()) {
     	ShowMessage("Input fields should not be empty");
        return;
     }

     if (BtAddSave1->Caption == "Add") {

         if (isNewItem(EWord->Text)) {
     		updateItem(EWord->Text, CBCategory->Text, EDefinition->Text, ESynonyms->Text);
         }
         else {
         	ShowMessage("The word is already in the list");
            return;
         }

     }
    else if (BtAddSave1->Caption == "Save") {

         if (!isEqualItem(EWord->Text, CBCategory->Text, EDefinition->Text, ESynonyms->Text)) {
     		updateItem(EWord->Text, CBCategory->Text, EDefinition->Text, ESynonyms->Text);
         }
         else {
         	ShowMessage("Nothing was changed");
            return;
         }
     }

     if (BtAddSave1->Caption == "Add") {
     	resetFrameFields();
     }

    UnicodeString msg = BtAddSave1->Caption == "Add" ? "Added" : "Saved";
    UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, msg);

}


bool TFrGeneratedText::isNewItem(const UnicodeString &text) {
     return dictionary->isInDictionary(text);
}


bool TFrGeneratedText::isEqualItem(const UnicodeString &word, const UnicodeString &category, const UnicodeString &definition, const UnicodeString &synonyms) {
  	 return dictionary->isEqualToDictionaryItem(DictionaryEntry(word, EnumUtils::stringToEnum<WordCategory>(DictionaryEntry::getEnumStrings(), category), \
    	definition, TextUtils::splitToTokens(synonyms)));
}


void TFrGeneratedText::updateItem(const UnicodeString &word, const UnicodeString &category, const UnicodeString &definition, const UnicodeString &synonyms)  {
   	dictionary->addDictionaryEntry(word, DictionaryEntry(word, EnumUtils::stringToEnum<WordCategory>(DictionaryEntry::getEnumStrings(), category), \
    	definition, TextUtils::splitToTokens(synonyms)));
}


void __fastcall TFrGeneratedText::CBDictionaryFilesChange(TObject *Sender) {

    dictionary->setDictionary(CBDictionaryFiles->Text);
    resetFrameFields();
}

void __fastcall TFrGeneratedText::msgDisplayTimerTimer(TObject *Sender) {
     UIUtils::removeTimedMessage(msgDisplayTimer, LInfo);
}

void __fastcall TFrGeneratedText::BtConvertClick(TObject *Sender) {

	if (!FConverter) {
		FConverter = std::make_unique<TFConverter>(nullptr, dataModule);
		FConverter->Position = poMainFormCenter;
	}
	FConverter->Show();
}


void TFrGeneratedText::setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item) {

    if (componentName == "FIleDialog") {
    	UIUtils::setFileDialogProperties(DFileOpen, item, "json");
    }
    else if (componentName == "Word" || componentName == "Definition" || componentName == "Synonyms") {
    	TEdit *edit = dynamic_cast<TEdit*>(this->FindComponent(L"E" + componentName));

        if (edit) {
            UIUtils::setEditText(edit, item);
        }
    }
}

void TFrGeneratedText::selectItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item) {

    if (componentName == "Category") {

    	int index = CBCategory->Items->IndexOf(item);

        UIUtils::selectComboBoxItem(CBCategory, index);

    }
}

void TFrGeneratedText::setItemsMultiItemControl(const UnicodeString& componentName, const std::vector<UnicodeString>& items, int selectedIndex) {

	if (componentName == "Category" || componentName == "DictionaryFiles") {
        TComboBox *comboBox = dynamic_cast<TComboBox*>(FindComponent(L"CB" + componentName));

        if (comboBox) {
            UIUtils::setComboBoxItems(comboBox, items, selectedIndex);
        }
    }
    else if (componentName == "Dictionary")  {
       UIUtils::setListViewItems(LVDictionary, items, selectedIndex);
    }

}

void TFrGeneratedText::addItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item, int selectedIndex) {

    if (componentName == "DictionaryFiles") {
    	UIUtils::addComboBoxItem(CBDictionaryFiles, item, selectedIndex);
    }
}


void __fastcall TFrGeneratedText::BtGenerateClick(TObject *Sender)
{

    if (CBDictionaryFiles->ItemIndex != -1) {

    	if ((CBCharsWordMax->Text != UnicodeString(L'\u221E') && StrToInt(CBCharsWordMin->Text) > StrToInt(CBCharsWordMax->Text)) \
        	|| StrToInt(CBWordsMin->Text) > StrToInt(CBWordsMax->Text)) {
            ShowMessage("Min value should be <= max value");
        }

        std::vector<UnicodeString> wordList;

        if (CBSynonyms->Checked) {

           std::vector<DictionaryEntry> dictionaryEntries = dictionary->getDictionaryValues();

           for (const DictionaryEntry &entry: dictionaryEntries)  {

                std::vector<UnicodeString> synonyms = entry.getSynonyms();
        		wordList.insert(wordList.end(), synonyms.begin(), synonyms.end());
           }
        }
        else {
        	wordList = dictionary->getDictionaryKeys();
        }

        //   generate text from word list (Generator/ TextService SOAP)

        Generator generator(false, CBUppercase->Checked, false);

        UnicodeString generatedText = generator.generateText(wordList, StrToInt(CBCharsWordMin->Text), \
        	CBCharsWordMax->Text == UnicodeString(L'\u221E') ? 0 : StrToInt(CBCharsWordMax->Text), \
         	StrToInt(CBWordsMin->Text), StrToInt(CBWordsMax->Text));

        MPreview->Clear();

        MPreview->Lines->BeginUpdate();

        if (!generatedText.IsEmpty()) {

        	MPreview->Font->Color = TColor(0xED9564);
            MPreview->Lines->Add(generatedText);
        }
        else {
          MPreview->Font->Color = TColor(0x0045FF);
          MPreview->Lines->Add("No matching words");
        }
        MPreview->Lines->EndUpdate();
    }

}

void __fastcall TFrGeneratedText::BtShuffleClick(TObject *Sender)
{
     if (CBDictionaryFiles->ItemIndex != -1) {

        if (ContainsText(MPreview->Lines->Text, "Preview")) {
            ShowMessage("Generate text before shuffle");
        }

        //   shuffle words in generated text (Generator/ TextService SOAP)

        Generator generator(false, CBUppercase, false);
        UnicodeString shuffledText = generator.shuffleWords(MPreview->Lines->Text);

        MPreview->Clear();

        MPreview->Lines->BeginUpdate();

        if (!shuffledText.IsEmpty()) {
            MPreview->Lines->Add(shuffledText);
        }
        MPreview->Lines->EndUpdate();
     }
}

// fetch synonyms and word category (Datamuse REST)

void __fastcall TFrGeneratedText::BtSynonymsClick(TObject *Sender)
{
    if (EWord->Text.IsEmpty()) {
		ShowMessage("No word selected");
        return;
    }

    dataModule->RESTClient->BaseURL = "https://api.datamuse.com/words?rel_syn=" + EWord->Text + "&max=5";

    dataModule->RESTResponseDataSetAdapter->TypesMode = TJSONTypesMode::StringOnly;
    dataModule->RESTResponse->RootElement = "";
    dataModule->RESTRequest->Method = rmGET;
    dataModule->RESTRequest->Execute();

    if (dataModule->FDMemTable->RecordCount) {

        dataModule->FDMemTable->First();
        UnicodeString synonyms = dataModule->FDMemTable->FieldByName("word")->AsString;
        ESynonyms->Text = synonyms;
    }

    dataModule->RESTClient->BaseURL = "https://api.datamuse.com/words?sp=" + EWord->Text + "&md=d&max=1";
    dataModule->RESTRequest->Execute();
    dataModule->RESTResponse->RootElement = "[0].defs[0]";

    UnicodeString defintion = dataModule->RESTResponse->JSONText;
    defintion = UnicodeString(TextUtils::trimCharacters(defintion, L'\"'));

    defintion = StringReplace(defintion, _D("\\t"), _D("\t"), TReplaceFlags() << rfReplaceAll);
    defintion = TextUtils::replaceChar(defintion, L'.', L' ');
    std::vector<UnicodeString> tokens = TextUtils::splitToTokens(defintion, L'\t');
    UnicodeString wordType = tokens[0];

    if (wordType == "adj") {
      selectItemMultiItemControl("Category", "Adjective");
    }
    else if (wordType == "adv") {
      selectItemMultiItemControl("Category", "Adverb");
    }
    else if (wordType == "n") {
      selectItemMultiItemControl("Category", "Noun");
    }
    else if (wordType == "v") {
      selectItemMultiItemControl("Category", "Verb");
    }

    EDefinition->Text = TextUtils::vectorToString(std::vector<UnicodeString>(tokens.begin() + 1, tokens.end())).LowerCase();

    dataModule->RESTResponse->RootElement = "";

}
//---------------------------------------------------------------------------

