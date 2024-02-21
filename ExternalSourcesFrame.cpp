//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExternalSourcesFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrExternalSources *FrExternalSources;
//---------------------------------------------------------------------------
__fastcall TFrExternalSources::TFrExternalSources(TComponent* Owner) : TFrame(Owner) {

   	_di_IXMLlibraryType library = Getlibrary(XMLDocument);

	for (int i = 0; i < library->Count; i++) {

		_di_IXMLcategoryType bookCategory = library->category[i];

		for (int j = 0; j < bookCategory->Count; j++) {

			_di_IXMLgenreType bookGenre =  bookCategory->genre[j];

            	mapOfBooks[bookGenre->Get_name()] = std::vector<_di_IXMLbookType>();

			for (int k = 0; k < bookGenre->Count; k++) {

				mapOfBooks[bookGenre->Get_name()].push_back(bookGenre->book[k]);

			}
		}
	}
}

//---------------------------------------------------------------------------

void __fastcall TFrExternalSources::TVLiteratureCategoriesChange(TObject *Sender, TTreeNode *Node)
{

	if (Node) {

    	MParagraph->Clear();
    	resetFrameFields();
        LVLiteratureDetails->Items->Clear();

        if (!Node->HasChildren) {
        	updateListView(Node);

        }
	}
}
//---------------------------------------------------------------------------

void TFrExternalSources::updateListView(TTreeNode* Node)
{
	LVLiteratureDetails->Items->Clear();
    BtAddSave2->Caption = "Add";
    BtDelete2->Enabled = false;

	if (!Node->HasChildren) {

		UnicodeString genre = Node->Text.LowerCase();

		std::map<UnicodeString, std::vector<_di_IXMLbookType>>::iterator it = mapOfBooks.find(genre);

		if (it != mapOfBooks.end()) {

			booksInGenre = it->second;

   			for (const _di_IXMLbookType& book : booksInGenre) {
				TListItem* item = LVLiteratureDetails->Items->Add();
				item->Caption = book->Get_author();
				item->SubItems->Add(book->Get_title());
				item->SubItems->Add(IntToStr(book->Get_year()));

            }
		}
	}
}

void TFrExternalSources::updateParagraph(int index) {

	MParagraph->Clear();

	MParagraph->Lines->BeginUpdate();
    if (booksInGenre.size() > index) {
        MParagraph->Lines->Add(booksInGenre[index]->Get_paragraph());
    }
    MParagraph->Lines->EndUpdate();
}

void TFrExternalSources::updateFields(int index)  {

    resetFrameFields();
    if (booksInGenre.size() > index) {

    	EAuthor->Text = booksInGenre[index]->Get_author();
        ETitle->Text = booksInGenre[index]->Get_title();
        EYear->Text = booksInGenre[index]->Get_year();
        EParagraph->Text = booksInGenre[index]->Get_paragraph();
    }
}


void __fastcall TFrExternalSources::LVLiteratureDetailsSelectItem(TObject *Sender, TListItem *Item, bool Selected)  {

   	if (LVLiteratureDetails->Selected) {

    	updateParagraph(LVLiteratureDetails->ItemIndex);
        updateFields(LVLiteratureDetails->ItemIndex);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrExternalSources::LVLiteratureDetailsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (LVLiteratureDetails->SelCount == 1) {
    	BtAddSave2->Caption = "Save";
    	BtDelete2->Enabled = true;
	}
	else if (LVLiteratureDetails->SelCount > 1) {

		TItemStates selected = TItemStates() << isSelected;
		TListItem *Item = LVLiteratureDetails->GetNextItem(Item, sdAll, selected);

		while (Item) {
			Item->Selected = false;
			Item = LVLiteratureDetails->GetNextItem(Item, sdAll, selected);
		}
	}
	else {

		if (LVLiteratureDetails->ItemFocused) {
           LVLiteratureDetails->ItemFocused->Focused = false;
		}
        resetFrameFields();
        MParagraph->Clear();
	}
}

void TFrExternalSources::resetFrameFields() {

	BtAddSave2->Caption = "Add";
    BtDelete2->Enabled = false;

    EAuthor->Text = "";
	ETitle->Text = "";
	EYear->Text = "";
	EParagraph->Text = "";
}



void __fastcall TFrExternalSources::BtAddSave2Click(TObject *Sender)  {

    if (!TVLiteratureCategories->Selected) {
    	ShowMessage("Select a book genre.");
        return;
    }
   	if (EAuthor->Text.IsEmpty() || ETitle->Text.IsEmpty() || EYear->Text.IsEmpty() || EParagraph->Text.IsEmpty()) {
     	ShowMessage("Input fields should not be empty.");
        return;
     }

    if (BtAddSave2->Caption.Compare("Add") == 0) {

       	_di_IXMLlibraryType library = Getlibrary(XMLDocument);
        TTreeNode *parentNode = TVLiteratureCategories->Selected->Parent;

        _di_IXMLbookType book = library->category[parentNode->Index]->genre[TVLiteratureCategories->Selected->Index]->Add();

        book->Set_author(EAuthor->Text);
        book->Set_title(ETitle->Text);
        book->Set_year(StrToInt(EYear->Text));
        book->Set_paragraph(EParagraph->Text);

        mapOfBooks[TVLiteratureCategories->Selected->Text.LowerCase()].push_back(book);
        MParagraph->Clear();
        resetFrameFields();
    }

    else if (BtAddSave2->Caption.Compare("Save") == 0)  {

    	_di_IXMLbookType book = booksInGenre[LVLiteratureDetails->ItemIndex];

        if (EAuthor->Text.Compare(book->Get_author()) == 0 && ETitle->Text.Compare(book->Get_title()) == 0 \
    		&& EYear->Text.Compare(IntToStr(book->Get_year())) == 0 && EParagraph->Text.Compare(book->Get_paragraph()) == 0) {

            ShowMessage("Nothing to save.");
            return;
        }
        else {

            _di_IXMLlibraryType library = Getlibrary(XMLDocument);
            TTreeNode *parentNode = TVLiteratureCategories->Selected->Parent;

            library->category[parentNode->Index]->genre[TVLiteratureCategories->Selected->Index]->book[LVLiteratureDetails->ItemIndex]->Set_author(EAuthor->Text);
            library->category[parentNode->Index]->genre[TVLiteratureCategories->Selected->Index]->book[LVLiteratureDetails->ItemIndex]->Set_title(ETitle->Text);
            library->category[parentNode->Index]->genre[TVLiteratureCategories->Selected->Index]->book[LVLiteratureDetails->ItemIndex]->Set_year(StrToInt(EYear->Text));
            library->category[parentNode->Index]->genre[TVLiteratureCategories->Selected->Index]->book[LVLiteratureDetails->ItemIndex]->Set_paragraph(EParagraph->Text);

            _di_IXMLbookType book = library->category[parentNode->Index]->genre[TVLiteratureCategories->Selected->Index]->book[LVLiteratureDetails->ItemIndex];

            mapOfBooks[TVLiteratureCategories->Selected->Text.LowerCase()][LVLiteratureDetails->ItemIndex] = book;

        }
    }

    XMLDocument->SaveToFile(XMLDocument->FileName);
    updateListView(TVLiteratureCategories->Selected);
}


void __fastcall TFrExternalSources::BtDelete2Click(TObject *Sender) {

    if (!TVLiteratureCategories->Selected) {
    	ShowMessage("Select a book genre.");
        return;
    }

    _di_IXMLlibraryType library = Getlibrary(XMLDocument);
    TTreeNode *parentNode = TVLiteratureCategories->Selected->Parent;

	library->category[parentNode->Index]->genre[TVLiteratureCategories->Selected->Index]->Delete(LVLiteratureDetails->ItemIndex);

    std::vector<_di_IXMLbookType> books = mapOfBooks[TVLiteratureCategories->Selected->Text.LowerCase()];
    books.erase(books.begin() + LVLiteratureDetails->Selected->Index);
    mapOfBooks[TVLiteratureCategories->Selected->Text.LowerCase()] = books;

    XMLDocument->SaveToFile(XMLDocument->FileName);

    updateListView(TVLiteratureCategories->Selected);
    MParagraph->Clear();
    resetFrameFields();

}
//---------------------------------------------------------------------------

