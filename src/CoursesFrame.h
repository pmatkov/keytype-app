//---------------------------------------------------------------------------

#ifndef CoursesFrameH
#define CoursesFrameH
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
class TFrCourses : public TFrame
{
__published:	// IDE-managed Components
	TDBGrid *DBGridCourses;
	TButton *BtDelete;
	TGroupBox *GBCourses;
	TLabel *LName;
	TLabel *LDescription;
	TLabel *LDifficulty;
	TLabel *LGoal;
	TLabel *LLanguage;
	TButton *BtAddSave;
	TButton *BtClearSelection;
	TEdit *EName;
	TEdit *EDescription;
	TComboBox *CBDifficulty;
	TComboBox *CBGoal;
	TComboBox *CBLanguage;
	TComboBox *CBFilter;
	TEdit *EFilter;
	TButton *BtFilter;
	TEdit *ESort;
	TButton *BtSort;
	TEdit *EGoalValue;
	TLabel *LGoalValue;
	void __fastcall DBGridCoursesCellClick(TColumn *Column);
	void __fastcall BtDeleteClick(TObject *Sender);
	void __fastcall BtClearSelectionClick(TObject *Sender);
	void __fastcall BtAddSaveClick(TObject *Sender);
	void __fastcall BtFilterClick(TObject *Sender);
	void __fastcall BtSortClick(TObject *Sender);
private:	// User declarations
    TDataModule1 *dataModule;
public:		// User declarations
	__fastcall TFrCourses(TComponent* Owner);
	__fastcall TFrCourses(TComponent* Owner, TDataModule1 *_dataModule);

    bool areFieldsEmpty();
    void clearInputFields();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrCourses *FrCourses;
//---------------------------------------------------------------------------
#endif
