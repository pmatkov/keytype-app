//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LessonsFrame.h"
#include "UIUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrLessons *FrLessons;
//---------------------------------------------------------------------------
__fastcall TFrLessons::TFrLessons(TComponent* Owner) : TFrame(Owner)  {}

__fastcall TFrLessons::TFrLessons(TComponent* Owner, TDataModule1 *_dataModule) : TFrame(Owner) {
	if (_dataModule) {

    	dataModule = _dataModule;
        dataModule->TLessons->MasterSource = dataModule->DCourses;

        UIUtils::setComboBoxItems(CBFilter, dataModule->getColumnNames(DBGridLessons->DataSource->DataSet, "courseName"), -1);

       	LOGGER(LogLevel::Debug, "Created frame lessons");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFrLessons::DBGridLessonsCellClick(TColumn *Column)
{

    EName->Text = DBGridLessons->DataSource->DataSet->FieldByName("name")->AsString;
    EInstructions->Text = DBGridLessons->DataSource->DataSet->FieldByName("instructions")->AsString;
    ECharacters->Text = DBGridLessons->DataSource->DataSet->FieldByName("characters")->AsString;
    EWordCount->Text = DBGridLessons->DataSource->DataSet->FieldByName("wordCount")->AsString;
    ECharCount->Text = DBGridLessons->DataSource->DataSet->FieldByName("charCount")->AsString;

    TFormatSettings formatSettings = {.ShortDateFormat = "dd.mm.yyyy"};
    EDateModified->Text = DateToStr(DBGridLessons->DataSource->DataSet->FieldByName("dateModified")->AsDateTime, FormatSettings);

   	BtAddSave->Caption = "Save";
}

void __fastcall TFrLessons::BtClearSelectionClick(TObject *Sender)
{
	clearInputFields();
}

void __fastcall TFrLessons::BtAddSaveClick(TObject *Sender)
{

	if (areFieldsEmpty()) {
 		ShowMessage("Input fields should not be empty");
        return;
     }

    if (BtAddSave->Caption == "Add") {

        if (BtMasterDetail->Caption == "Master off") {
            ShowMessage("Enable master/ detail before adding records");
        }
        else {
        	DBGridLessons->DataSource->DataSet->Append();
        }

    }
     else if (BtAddSave->Caption == "Save") {

     	DBGridLessons->DataSource->DataSet->Edit();

     }

     DBGridLessons->DataSource->DataSet->FieldByName("name")->AsString = EName->Text;
     DBGridLessons->DataSource->DataSet->FieldByName("instructions")->AsString = EInstructions->Text;
     DBGridLessons->DataSource->DataSet->FieldByName("characters")->AsString = ECharacters->Text;
     DBGridLessons->DataSource->DataSet->FieldByName("wordCount")->AsInteger = StrToInt(EWordCount->Text);
     DBGridLessons->DataSource->DataSet->FieldByName("charCount")->AsInteger = StrToInt(ECharCount->Text);

     TFormatSettings formatSettings = {.ShortDateFormat = "dd.mm.yyyy"};
     DBGridLessons->DataSource->DataSet->FieldByName("dateModified")->AsDateTime = StrToDate(EDateModified->Text, FormatSettings);

     DBGridLessons->DataSource->DataSet->Post();

     if (BtAddSave->Caption == "Add") {
     	clearInputFields();
    }
}


void __fastcall TFrLessons::BtDeleteClick(TObject *Sender)
{
   if (DBGridLessons->SelectedRows->Count) {
     DBGridLessons->DataSource->DataSet->Delete();
     clearInputFields() ;
   }
   else {
   		ShowMessage("Select record to delete");
   }
}

bool TFrLessons::areFieldsEmpty() {
   return (EName->Text.IsEmpty() || EInstructions->Text.IsEmpty() || ECharacters->Text.IsEmpty() || EWordCount->Text.IsEmpty() ||  ECharCount->Text.IsEmpty() || EDateModified->Text.IsEmpty());
}


void TFrLessons::clearInputFields() {

	DBGridLessons->SelectedRows->Clear();

    EName->Text = "";
    EInstructions->Text = "";
    ECharacters->Text = "";
    EWordCount->Text = "";
    ECharCount->Text = "";
    EDateModified->Text = "";

    GBLessons->SetFocus();

    BtAddSave->Caption = "Add";
}

// filter lessons

void __fastcall TFrLessons::BtFilterClick(TObject *Sender)
{

    if (CBFilter->Text != "") {
    	DBGridLessons->DataSource->DataSet->Filter = CBFilter->Text + " LIKE '%" + EFilter->Text + "%'";
       	DBGridLessons->DataSource->DataSet->Filtered = true;
    }
}

// sort lessons

void __fastcall TFrLessons::BtSortClick(TObject *Sender)
{

    if (ESort->Text == "") {
      	dataModule->TLessons->IndexFieldNames = "idCourses";
    }
    else {
      	dataModule->TLessons->IndexFieldNames = ESort->Text;
    }

}

// enable/ disable master-detail relationship

void __fastcall TFrLessons::BtMasterDetailClick(TObject *Sender)
{

	if (BtMasterDetail->Caption == "Master off") {
      	dataModule->TLessons->MasterSource = nullptr;
      	BtMasterDetail->Caption = "Master on";
    }
    else if (BtMasterDetail->Caption == "Master on") {
    	dataModule->TLessons->MasterSource = dataModule->DCourses;
        BtMasterDetail->Caption = "Master off";
    }
}
//---------------------------------------------------------------------------

