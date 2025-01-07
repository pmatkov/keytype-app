//---------------------------------------------------------------------------

#ifndef ExternalSourcesFrameH
#define ExternalSourcesFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XmlTransform.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <vector>
#include <map>

#include "Books.h"
//---------------------------------------------------------------------------
class TFrExternalSources : public TFrame
{
__published:	// IDE-managed Components

	TTreeView *TVLiteratureCategories;
	TListView *LVLiteratureDetails;
	TMemo *MParagraph;
	TLabel *LAuthor;
	TLabel *LTitle;
	TLabel *LYear;
	TEdit *EAuthor;
	TEdit *ETitle;
	TEdit *EYear;
	TLabel *LParagraph;
	TEdit *EParagraph;
	TButton *BtDelete;
	TButton *BtAddSave;
	TXMLTransform *XMLTransform;
	TXMLDocument *XMLDocument;
	void __fastcall TVLiteratureCategoriesChange(TObject *Sender, TTreeNode *Node);
	void __fastcall LVLiteratureDetailsSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall BtAddSaveClick(TObject *Sender);
	void __fastcall LVLiteratureDetailsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall BtDeleteClick(TObject *Sender);

private:	// User declarations
        std::map<UnicodeString, std::vector<_di_IXMLbookType>> mapOfBooks;
        std::vector<_di_IXMLbookType> booksInGenre;

public:		// User declarations
	__fastcall TFrExternalSources(TComponent* Owner);
    void updateParagraph(int index);
    void updateFields(int index);
    void updateListView(TTreeNode* selectedNode);
    void resetFrameFields();

};
//---------------------------------------------------------------------------
extern PACKAGE TFrExternalSources *FrExternalSources;
//---------------------------------------------------------------------------
#endif
