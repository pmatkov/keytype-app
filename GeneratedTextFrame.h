//---------------------------------------------------------------------------

#ifndef GeneratedTextFrameH
#define GeneratedTextFrameH
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
#include <vector>
#include <optional>

#include "WordList.h"
#include "Dictionary.h"

//---------------------------------------------------------------------------
class TFrGeneratedText : public TFrame
{
__published:	// IDE-managed Components

	TRadioGroup *RGGeneratedText;
	TGroupBox *GBCharacters;
	TBevel *BvCharSource;
	TToolBar *TBLetters;
	TCheckBox *CBSelectAll;
	TCheckBox *CBNumbers;
	TCheckBox *CBPunctuation;
	TCheckBox *CBCapitalLetters;
	TGroupBox *GBWords;
	TLabel *LWordList;
	TLabel *LDefinition;
	TLabel *LSynonym;
	TLabel *LCategory;
	TLabel *LWord;
	TButton *BtBrowse;
	TComboBox *CBTextFiles;
	TListView *LVWords;
	TEdit *EWord;
	TEdit *EDefinition;
	TEdit *ESynonyms;
	TComboBox *CBCategory;
	TButton *BtAddSave1;
	TButton *BtDelete1;
	TOpenTextFileDialog *DFileOpen;
	TLabel *LInfo;
	TTimer *msgDisplayTimer;

    void __fastcall RGGeneratedTextClick(TObject *Sender);

    void __fastcall CBSelectAllClick(TObject *Sender);
    void __fastcall BtBrowseClick(TObject *Sender);
	void __fastcall BtDelete1Click(TObject *Sender);
	void __fastcall BtAddSave1Click(TObject *Sender);
	void __fastcall CBTextFilesChange(TObject *Sender);
    void __fastcall LVWordsSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall msgDisplayTimerTimer(TObject *Sender);
	void __fastcall LVWordsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

private:	// User declarations
   std::vector<TToolButton*> buttons;
   std::vector<WordList> wordListCollection;
   Dictionary dictionary;

public:		// User declarations
	__fastcall TFrGeneratedText(TComponent* Owner);
	__fastcall ~TFrGeneratedText();

     void displayTimedMessage(TTimer *timer, TLabel *label, const UnicodeString &msg);

    void createTBButtons(TToolBar* toolbar, int count);
    void deleteTBButtons(std::vector<TToolButton*> buttons);
    const std::vector<TToolButton*>& getButtons() const;

    void setGroupBoxState(TRadioGroup* radiogroup, TGroupBox *primary, TGroupBox *secondary);

    void loadWordLists(const UnicodeString &path, TComboBox *comboBox, TListView *listview, std::vector<WordList> &wordListCollection);

    void setComboBoxItems(TComboBox *comboBox, const std::vector<UnicodeString> &items, int defaultIndex);
    void setListViewItems(TListView *listview, const std::vector<UnicodeString> &items);

    void resetFrameFields(bool all);
    bool fieldsAreEmpty();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrGeneratedText *FrGeneratedText;

//---------------------------------------------------------------------------
#endif
