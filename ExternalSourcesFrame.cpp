//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExternalSourcesFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrExternalSources *FrExternalSources;
//---------------------------------------------------------------------------
__fastcall TFrExternalSources::TFrExternalSources(TComponent* Owner)
	: TFrame(Owner)
{

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
//---------------------------------------------------------------------------

void __fastcall TFrExternalSources::TVLiteratureCategoriesChange(TObject *Sender, TTreeNode *Node)
{

	if (Node) {
		updateListView(Node);
	}
}
//---------------------------------------------------------------------------

void TFrExternalSources::updateListView(TTreeNode* selectedNode)
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


//---------------------------------------------------------------------------


