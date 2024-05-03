//---------------------------------------------------------------------------

#include <vcl.h>


#include "Factory.h"
#include "GeneratedTextFrame.h"
#include "PracticeForm.h"
#include "UIUtils.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "Dictionary.h"
#include "DictionaryEntry.h"
#include "EnumUtils.h"
#include "Logger.h"
#include "EDirNotFoundException.h"

#define LETTERS 26
#define BUTTON_SIZE 18

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrGeneratedText *FrGeneratedText;

//---------------------------------------------------------------------------
__fastcall TFrGeneratedText::TFrGeneratedText(TComponent* Owner) : TFrame(Owner), dictionary(ModelFactory::createDictionary(*this, *this)) {}

void __fastcall TFrGeneratedText::BtBrowseClick(TObject *Sender) {

  UIUtils::setFileDialogProperties(DFileOpen, "Data", "json");

	if (DFileOpen->Execute()) {

		 if (FileExists(DFileOpen->FileName)) {

             // extracts filename and extension from path
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
     	ShowMessage("Input fields should not be empty.");
        return;
     }

     if (BtAddSave1->Caption == "Add") {

         if (isNewItem(EWord->Text)) {
     		updateItem(EWord->Text, CBCategory->Text, EDefinition->Text, ESynonyms->Text);
         }
         else {
         	ShowMessage("The word is already in the list.");
            return;
         }

     }
    else if (BtAddSave1->Caption == "Save") {

         if (isEqualItem(EWord->Text, CBCategory->Text, EDefinition->Text, ESynonyms->Text)) {
     		updateItem(EWord->Text, CBCategory->Text, EDefinition->Text, ESynonyms->Text);
         }
         else {
         	ShowMessage("The word is already in the list.");
            return;
         }
     }

    resetFrameFields();
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
		FConverter = std::make_unique<TFConverter>(nullptr);
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

    	if (index != -1) {
        	UIUtils::selectComboBoxItem(CBCategory, index);
        }
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


