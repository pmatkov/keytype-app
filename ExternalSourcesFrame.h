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
	TButton *BtDelete2;
	TButton *BtAddSave2;
	TXMLTransform *XMLTransform1;
	TXMLDocument *XMLDocument1;
	void __fastcall TVLiteratureCategoriesChange(TObject *Sender, TTreeNode *Node);

private:	// User declarations
        std::map<UnicodeString, std::vector<_di_IXMLbookType>> mapOfBooks;
public:		// User declarations
	__fastcall TFrExternalSources(TComponent* Owner);
    void updateListView(TTreeNode* selectedNode);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrExternalSources *FrExternalSources;
//---------------------------------------------------------------------------
#endif
