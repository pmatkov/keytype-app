//---------------------------------------------------------------------------

#ifndef PracticeFormH
#define PracticeFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.AppEvnts.hpp>
#include <vcl.h>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XmlTransform.hpp>
#include <memory>
#include <vector>
#include <map>

#include "WordList.h"
#include "Dictionary.h"
#include "Books.h"
#include "SessionModule.h"


//---------------------------------------------------------------------------
class TFPractice : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PCSourceText;
	TTabSheet *TSGeneratedText;
	TTabSheet *TSCustomText;
	TTabSheet *TSExternalSources;
	TButton *BtAccept;
	TButton *BtCancel;

	TRadioGroup *RGGeneratedText;
	TGroupBox *GBCharacters;
	TGroupBox *GBWords;
	TToolBar *TBLetters;
	TCheckBox *CBSelectAll;
	TCheckBox *CBNumbers;
	TCheckBox *CBPunctuation;
	TBevel *BvCharSource;
	TCheckBox *CBCapitalLetters;
	TLabel *LWordList;
	TButton *BtBrowse;
	TComboBox *CBTextFiles;
	TListView *LVWords;
	TLabel *LDefinition;
	TLabel *LSynonym;
	TLabel *LCategory;
	TLabel *LWord;
	TEdit *EWord;
	TEdit *EDefinition;
	TEdit *ESynonyms;
	TComboBox *CBCategory;
	TButton *BtAddSave1;
	TButton *BtDelete1;
	TTreeView *TVLiteratureCategories;
	TOpenTextFileDialog *DFileOpen;
	TListView *LVLiteratureDetails;
	TMemo *MParagraph;
	TXMLDocument *XMLDocument1;
	TXMLTransform *XMLTransform1;
	TLabel *LParagraph;
	TEdit *EAuthor;
	TLabel *LAuthor;
	TLabel *LTitle;
	TEdit *ETitle;
	TEdit *EYear;
	TLabel *LYear;
	TButton *BtAddSave2;
	TButton *BtDelete2;
	TEdit *EParagraph;

	void __fastcall RGGeneratedTextClick(TObject *Sender);
	void __fastcall CBSelectAllClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtBrowseClick(TObject *Sender);
	void __fastcall CBTextFilesChange(TObject *Sender);
	void __fastcall LVWordsSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall LVWordsChange(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall BtDelete1Click(TObject *Sender);
	void __fastcall BtAddSave1Click(TObject *Sender);
	void __fastcall BtAcceptClick(TObject *Sender);
	void __fastcall TVLiteratureCategoriesChange(TObject *Sender, TTreeNode *Node);

private:	// User declarations

	std::vector<TToolButton*> buttons;
	std::vector<WordList> wordListCollection;
    std::map<UnicodeString, std::vector<_di_IXMLbookType>> mapOfBooks;

	// da li je potreban?
	SessionModule *sessionModule;

	Dictionary dictionary;

	int cbTextFilesPrevIndex;
	bool wordInDictionary;
	bool listChanged;

public:		// User declarations
	__fastcall TFPractice(TComponent* Owner);
	__fastcall ~TFPractice();

	void setSessionModule(SessionModule *_sessionModule);

	void updateGroupBoxState();
	void changeChildControlsStatus(TWinControl* parentControl, Boolean status);
	const std::vector<TToolButton*>& getButtons() const;
	void loadWordListFromFile(const UnicodeString &filename);
	void loadListViewItems();
	void clearInputFields();
	void updateListView(TTreeNode* selectedNode);


};
//---------------------------------------------------------------------------
extern PACKAGE TFPractice *FPractice;
//---------------------------------------------------------------------------
#endif
