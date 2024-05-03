//---------------------------------------------------------------------------

#ifndef LessonsFrameH
#define LessonsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>


#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>

#include "DataModule.h"

//---------------------------------------------------------------------------
class TFrLessons : public TFrame
{
__published:	// IDE-managed Components
	TDBGrid *DBGridLessons;
	TGroupBox *GBLessons;
	TButton *BtAddSave;
	TButton *BtDelete;
	TEdit *EName;
	TButton *BtClearSelection;
	TEdit *EInstructions;
	TLabel *LInstructions;
	TLabel *LName;
	TEdit *ECharacters;
	TLabel *LCharacters;
	TLabel *LWordCount;
	TEdit *EWordCount;
	TEdit *EDateModified;
	TLabel *LDateModified;
	TComboBox *CBFilter;
	TEdit *EFilter;
	TButton *BtFilter;
	TEdit *ECharCount;
	TLabel *LCharCount;
	TButton *BtSort;
	TEdit *ESort;
	TButton *BtMasterDetail;
	void __fastcall DBGridLessonsCellClick(TColumn *Column);
	void __fastcall BtClearSelectionClick(TObject *Sender);
	void __fastcall BtAddSaveClick(TObject *Sender);
	void __fastcall BtDeleteClick(TObject *Sender);
	void __fastcall BtFilterClick(TObject *Sender);
	void __fastcall BtSortClick(TObject *Sender);
	void __fastcall BtMasterDetailClick(TObject *Sender);
private:	// User declarations

    TDataModule1 *dataModule;

public:		// User declarations
	__fastcall TFrLessons(TComponent* Owner);
    __fastcall TFrLessons(TComponent* Owner, TDataModule1 *_dataModule);

    bool areFieldsEmpty();
    void clearInputFields();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrLessons *FrLessons;
//---------------------------------------------------------------------------
#endif
