//---------------------------------------------------------------------------


#pragma hdrstop

#include "DataModule.h"
#include <System.Math.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"

TDataModule1 *DataModule1;
//---------------------------------------------------------------------------
__fastcall TDataModule1::TDataModule1(TComponent* Owner)
	: TDataModule(Owner)
{
}

void __fastcall TDataModule1::TLessonsCalcFields(TDataSet *DataSet)
{
 	if (DataSet->State != dsInsert && DataSet->State != dsEdit) {
       float avgChar = static_cast<float>(TLessons->FieldByName("charCount")->AsInteger) / TLessons->FieldByName("wordCount")->AsInteger;
       TLessons->FieldByName("avgChars")->AsFloat = RoundTo(avgChar, -2);
    }
}

std::vector<UnicodeString> TDataModule1::getColumnNames(TDataSet *DataSet, const UnicodeString &exclude) {

    std::vector<UnicodeString> columnNames;

    for (int i = 0; i < DataSet->FieldCount; i++) {

     	TField *field = DataSet->Fields->Fields[i];
        if (exclude == "" || field->FieldName != exclude) {
            columnNames.push_back(field->FieldName);
        }
    }
    return columnNames;
}

std::vector<std::pair<int, UnicodeString>> TDataModule1::getColumnValues(TDataSet *DataSet, const UnicodeString &columnName) {

    std::vector<std::pair<int, UnicodeString>> columnValues;

    DataSet->First();

    while (!DataSet->Eof) {
        columnValues.push_back(std::make_pair(DataSet->FieldByName("id")->AsInteger, DataSet->FieldByName(columnName)->AsString));
        DataSet->Next();
    }
    DataSet->First();

    return columnValues;
}

std::vector<std::pair<int, UnicodeString>> TDataModule1::getColumnValues(TDataSet *DataSet, const UnicodeString &idName, const UnicodeString &columnName, int index)
{
    std::vector<std::pair<int, UnicodeString>> columnValues;

    DataSet->First();

    while (!DataSet->Eof) {
        if (DataSet->FieldByName(idName)->AsInteger == index) {
        	columnValues.push_back(std::make_pair(DataSet->FieldByName("id")->AsInteger, DataSet->FieldByName(columnName)->AsString));
        }
        DataSet->Next();
    }
    DataSet->First();

    return columnValues;
}

UnicodeString TDataModule1::getColumnValue(TDataSet *DataSet, const UnicodeString &columnName, int index)
{
    UnicodeString value = "";

  	DataSet->First();

    while (!DataSet->Eof) {
        if (DataSet->FieldByName("id")->AsInteger == index) {
        	value = DataSet->FieldByName(columnName)->AsString;
            break;
        }
        DataSet->Next();
    }
    DataSet->First();

    return value;
}

std::vector<UnicodeString> TDataModule1::getStringsFromColumnValues(const std::vector<std::pair<int, UnicodeString>> &pairs) {

    std::vector<UnicodeString> values;

	for (const std::pair<int, UnicodeString>& pair : pairs) {
        values.push_back(pair.second);
    }

    return values;
}

