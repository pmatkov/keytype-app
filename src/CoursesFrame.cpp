//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CoursesFrame.h"
#include "UIUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFrCourses *FrCourses;
//---------------------------------------------------------------------------
__fastcall TFrCourses::TFrCourses(TComponent* Owner) : TFrame(Owner) {}

__fastcall TFrCourses::TFrCourses(TComponent* Owner, TDataModule1 *_dataModule)	: TFrame(Owner) {

	if (_dataModule) {

    	dataModule = _dataModule;

    	UIUtils::setComboBoxItems(CBFilter, dataModule->getColumnNames(DBGridCourses->DataSource->DataSet, ""), -1);
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}
void __fastcall TFrCourses::DBGridCoursesCellClick(TColumn *Column)
{

    EName->Text = DBGridCourses->DataSource->DataSet->FieldByName("name")->AsString;
    EDescription->Text = DBGridCourses->DataSource->DataSet->FieldByName("description")->AsString;
    UIUtils::selectComboBoxItem(CBDifficulty, DBGridCourses->DataSource->DataSet->FieldByName("difficulty")->AsString);
    UIUtils::selectComboBoxItem(CBGoal, DBGridCourses->DataSource->DataSet->FieldByName("goal")->AsString);
   	EGoalValue->Text = DBGridCourses->DataSource->DataSet->FieldByName("goalValue")->AsInteger;
    UIUtils::selectComboBoxItem(CBLanguage, DBGridCourses->DataSource->DataSet->FieldByName("language")->AsString);

    BtAddSave->Caption = "Save";
}

void __fastcall TFrCourses::BtClearSelectionClick(TObject *Sender)
{
	clearInputFields();
}

void __fastcall TFrCourses::BtAddSaveClick(TObject *Sender)
{

   	if (areFieldsEmpty()) {
 		ShowMessage("Input fields should not be empty.");
        return;
    }

    if (BtAddSave->Caption == "Add") {

    	DBGridCourses->DataSource->DataSet->Append();

    }
    else if (BtAddSave->Caption == "Save") {

    	DBGridCourses->DataSource->DataSet->Edit();
    }

    DBGridCourses->DataSource->DataSet->FieldByName("name")->AsString = EName->Text;
    DBGridCourses->DataSource->DataSet->FieldByName("description")->AsString = EDescription->Text;
    DBGridCourses->DataSource->DataSet->FieldByName("difficulty")->AsInteger = StrToInt(CBDifficulty->Text);
    DBGridCourses->DataSource->DataSet->FieldByName("goal")->AsString = CBGoal->Text;
    DBGridCourses->DataSource->DataSet->FieldByName("goalValue")->AsInteger = StrToInt(EGoalValue->Text);
    DBGridCourses->DataSource->DataSet->FieldByName("language")->AsString = CBLanguage->Text;

    DBGridCourses->DataSource->DataSet->Post();

    if (BtAddSave->Caption == "Add") {
     	clearInputFields();
	}

}

void __fastcall TFrCourses::BtDeleteClick(TObject *Sender)
{
   if (DBGridCourses->SelectedRows->Count) {
     DBGridCourses->DataSource->DataSet->Delete();
     clearInputFields() ;
   }
   else {
   		ShowMessage("Select record to delete.");
   }
}

bool TFrCourses::areFieldsEmpty() {
   return (EName->Text.IsEmpty() || EDescription->Text.IsEmpty() || CBDifficulty->ItemIndex == -1 || CBGoal->ItemIndex == -1 || EGoalValue->Text.IsEmpty() || CBLanguage->ItemIndex == -1);
}

void TFrCourses::clearInputFields() {

	DBGridCourses->SelectedRows->Clear();

    EName->Text = "";
    EDescription->Text = "";
    UIUtils::selectComboBoxItem(CBDifficulty, -1);
    UIUtils::selectComboBoxItem(CBGoal, -1);
    EGoalValue->Text = "";
    UIUtils::selectComboBoxItem(CBLanguage, -1);

    GBCourses->SetFocus();
    BtAddSave->Caption = "Add";
}

// filter courses

void __fastcall TFrCourses::BtFilterClick(TObject *Sender)
{

    if (CBFilter->Text != "") {
    	DBGridCourses->DataSource->DataSet->Filter = CBFilter->Text + " LIKE '%" + EFilter->Text + "%'";
       	DBGridCourses->DataSource->DataSet->Filtered = true;
    }
}

// sort courses

void __fastcall TFrCourses::BtSortClick(TObject *Sender)
{

	if (ESort->Text == "") {

      dataModule->TCourses->IndexFieldNames = "";
    }
    else {
     	dataModule->TCourses->IndexFieldNames = ESort->Text;
    }

}
//---------------------------------------------------------------------------

