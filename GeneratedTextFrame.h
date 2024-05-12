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

#include <memory>

#include "DataModule.h"
#include "Dictionary.h"
#include "ISingleItemDisplay.h"
#include "IMultiItemDisplay.h"
#include "ConverterForm.h"

#if !defined(INTFOBJECT_IMPL_IUNKNOWN)
#define INTFOBJECT_IMPL_IUNKNOWN(BASE) \
    ULONG   __stdcall AddRef() { return BASE::_AddRef();} \
    ULONG   __stdcall Release(){ return BASE::_Release();} \
    HRESULT __stdcall QueryInterface(REFIID iid, void** p){ return BASE::QueryInterface(iid, p);}
#endif

//---------------------------------------------------------------------------
class TFrGeneratedText : public TFrame, public ISingleItemDisplay, public IMultiItemDisplay
{

	INTFOBJECT_IMPL_IUNKNOWN(TFrame)

__published:	// IDE-managed Components
	TGroupBox *GBWords;
	TLabel *LDictionary;
	TLabel *LDefinition;
	TLabel *LSynonym;
	TLabel *LCategory;
	TLabel *LWord;
	TButton *BtBrowse;
	TComboBox *CBDictionaryFiles;
	TListView *LVDictionary;
	TEdit *EWord;
	TEdit *EDefinition;
	TEdit *ESynonyms;
	TComboBox *CBCategory;
	TButton *BtAddSave1;
	TButton *BtDelete1;
	TOpenTextFileDialog *DFileOpen;
	TLabel *LInfo;
	TTimer *msgDisplayTimer;
	TLabel *LWordsMin;
	TComboBox *CBWordsMin;
	TComboBox *CBWordsMax;
	TLabel *LWordsMax;
	TCheckBox *CBNumbers;
	TCheckBox *CBPunctuation;
	TMemo *MPreview;
	TButton *BtTest;
	TButton *BtTestThreads;
	TButton *BtConvert;

    void __fastcall BtBrowseClick(TObject *Sender);
	void __fastcall BtDelete1Click(TObject *Sender);
	void __fastcall BtAddSave1Click(TObject *Sender);
	void __fastcall CBDictionaryFilesChange(TObject *Sender);
    void __fastcall LVDictionarySelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall msgDisplayTimerTimer(TObject *Sender);
	void __fastcall LVDictionaryMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall BtConvertClick(TObject *Sender);

private:	// User declarations
	TDataModule1 *dataModule;
	std::unique_ptr<Dictionary> dictionary;
    std::unique_ptr<TFConverter> FConverter;

public:		// User declarations
	__fastcall TFrGeneratedText(TComponent* Owner);
    __fastcall TFrGeneratedText(TComponent* Owner, TDataModule1 *_dataModule);

    void displayTimedMessage(TTimer *timer, TLabel *label, const UnicodeString &msg);

    void resetFrameFields();
    bool areFieldsEmpty();

    bool isNewItem(const UnicodeString &text);
    bool isEqualItem(const UnicodeString &word, const UnicodeString &category, const UnicodeString &definition, const UnicodeString &synonyms);
    void updateItem(const UnicodeString &word, const UnicodeString &category, const UnicodeString &definition, const UnicodeString &synonyms);

    void setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item);
    void selectItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item);
    void setItemsMultiItemControl(const UnicodeString& componentName, const std::vector<UnicodeString>& items, int selectedIndex);
    void addItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item, int selectedIndex);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrGeneratedText *FrGeneratedText;

//---------------------------------------------------------------------------
#endif
