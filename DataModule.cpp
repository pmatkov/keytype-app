//---------------------------------------------------------------------------


#pragma hdrstop

#include "DataModule.h"
#include "FileUtils.h"
#include "Logger.h"
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


void __fastcall TDataModule1::TLessonResultsCalcFields(TDataSet *DataSet)
{
	if (DataSet->State != dsInsert && DataSet->State != dsEdit) {

      int duration = TLessonResults->FieldByName("duration")->AsInteger;
      int hrs = duration / 3600;
      int min = (duration - (hrs * 3600)) / 60;
      int sec = (duration - (hrs * 3600)) % 60;

      UnicodeString hrsStr = (hrs < 10 ? "0" : "") + IntToStr(hrs);
      UnicodeString minStr = (min < 10 ? "0" : "") + IntToStr(min);
      UnicodeString secStr = (sec < 10 ? "0" : "") + IntToStr(sec);
      TLessonResults->FieldByName("durationHMS")->AsString = hrsStr + ":" + minStr + ":" + secStr;
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

UnicodeString TDataModule1::generateText(const UnicodeString &letters, bool useNumbers, bool useUppercase,  bool usePunctuation, int min, int max) {

    UnicodeString generatedText = "";

    try {
       try {
            IdTCPClient1->Connect();

            IdTCPClient1->IOHandler->WriteLn(1);
            IdTCPClient1->IOHandler->WriteLn(letters);
            IdTCPClient1->IOHandler->WriteLn(useNumbers);
            IdTCPClient1->IOHandler->WriteLn(useUppercase);
            IdTCPClient1->IOHandler->WriteLn(usePunctuation);
            IdTCPClient1->IOHandler->WriteLn(min);
            IdTCPClient1->IOHandler->WriteLn(max);

            generatedText = IdTCPClient1->Socket->ReadLn();

            LOGGER(LogLevel::Debug, "Client complete");
       }
       catch (Exception &ex) {
            LOGGER(LogLevel::Error, "Client error: " + ex.Message);
        }

    }
    __finally {

    	IdTCPClient1->Disconnect();

    }
    return generatedText;
}


bool TDataModule1::convertWordList(const UnicodeString& filePath) {

    try {
    	try {

            IdTCPClient1->Connect();

            IdTCPClient1->IOHandler->WriteLn(2);
     		IdTCPClient1->IOHandler->WriteLn(ExtractFileName(filePath));
    		std::unique_ptr<TFileStream> fileStream = std::make_unique<TFileStream>(filePath, fmOpenRead);

      		IdTCPClient1->IOHandler->LargeStream = true;
            IdTCPClient1->IOHandler->Write(fileStream.get(), 0, true);
            fileStream.reset();

            UnicodeString serverResponse = IdTCPClient1->IOHandler->ReadLn();

            if (serverResponse == "File converted") {
                UnicodeString convertedFilePath = FileUtils::traverseUpDirTree(filePath, 2) + "Data\\" + ExtractFileName(filePath);
                convertedFilePath = convertedFilePath.Delete(convertedFilePath.Length()-2, 3) + "json";

            	std::unique_ptr<TStream> fileStream = std::make_unique<TFileStream>(convertedFilePath, fmCreate);
            	IdTCPClient1->IOHandler->LargeStream = true;
        		IdTCPClient1->IOHandler->ReadStream(fileStream.get());

            	LOGGER(LogLevel::Debug, "Client complete");
                return true;
            }
       }
       catch (Exception &ex) {
            LOGGER(LogLevel::Error, "Client error: " + ex.Message);
        }

    }
    __finally {

    	IdTCPClient1->Disconnect();

    }
    return false;
}

