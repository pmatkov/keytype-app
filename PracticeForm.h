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
#include <memory>
#include <vector>

#include "WordList.h"
#include "Dictionary.h"


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
	TButton *BtAddSave;
	TButton *BtDelete;
	TTreeView *TreeView1;
	TOpenTextFileDialog *DFileOpen;

//	void __fastcall BtCancelClick(TObject *Sender);
	void __fastcall RGGeneratedTextClick(TObject *Sender);
	void __fastcall CBSelectAllClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtBrowseClick(TObject *Sender);
	void __fastcall CBTextFilesChange(TObject *Sender);
	void __fastcall LVWordsSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall LVWordsChange(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall BtDeleteClick(TObject *Sender);
	void __fastcall BtAddSaveClick(TObject *Sender);
	void __fastcall BtAcceptClick(TObject *Sender);


private:	// User declarations

//	std::vector<std::unique_ptr<TToolButton>> buttons;
	std::vector<TToolButton*> buttons;
	std::vector<WordList> wordListCollection;
	Dictionary dictionary;
	int cbTextFilesPrevIndex;
	bool wordInDictionary;
	bool listChanged;

public:		// User declarations
	__fastcall TFPractice(TComponent* Owner);
	__fastcall ~TFPractice();
	void updateGroupBoxState();
	void changeChildControlsStatus(TWinControl* parentControl, Boolean status);
	const std::vector<TToolButton*>& getButtons() const;
    void loadWordListFromFile(const UnicodeString &filename);
	void loadListViewItems();
	void clearInputFields();


//	const std::vector<std::unique_ptr<TToolButton>>& getButtons() const;

};
//---------------------------------------------------------------------------
extern PACKAGE TFPractice *FPractice;
//---------------------------------------------------------------------------
#endif
