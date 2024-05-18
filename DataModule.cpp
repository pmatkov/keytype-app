//---------------------------------------------------------------------------


#pragma hdrstop

#include "DataModule.h"
#include "FileUtils.h"
#include "CryptoUtils.h"
#include "Logger.h"
#include <System.Math.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma link "uTPLb_BaseNonVisualComponent"
#pragma link "uTPLb_Codec"
#pragma link "uTPLb_CryptographicLibrary"
#pragma link "uTPLb_Signatory"
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

UnicodeString TDataModule1::generateText(const UnicodeString &letters, bool useNumbers, bool useUppercase,  bool usePunctuation, int minTokens, int maxTokens) {

    UnicodeString generatedText = "";

    try {
       try {

       		std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
            std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
            std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory();
            signatory->Codec = codec.get();

       		UnicodeString prvKeyPath = FileUtils::createAbsolutePath("Keys\\prv_key_app.bin", true);
            UnicodeString pubKeyPath = FileUtils::createAbsolutePath("Keys\\pub_key_srv.bin", true);

            IdTCPClient1->Connect();

            LOGGER(LogLevel::Debug, "Connected to TCP server");

            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, "1"));
            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, letters));
            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(useNumbers)));
            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(useUppercase)));
            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(usePunctuation)));
            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(minTokens)));
            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(maxTokens)));

            generatedText = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, IdTCPClient1->IOHandler->ReadLn());

            LOGGER(LogLevel::Debug, "Socket I/O complete");
       }
       catch (Exception &ex) {
            LOGGER(LogLevel::Error, "TCP client error: " + ex.Message);
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

        	std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
            std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
            std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory();
            signatory->Codec = codec.get();

        	UnicodeString prvKeyPath = FileUtils::createAbsolutePath("Keys\\prv_key_app.bin", true);
            UnicodeString pubKeyPath = FileUtils::createAbsolutePath("Keys\\pub_key_srv.bin", true);

            IdTCPClient1->Connect();

            LOGGER(LogLevel::Debug, "Connected to TCP server");

			IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, "2"));
            IdTCPClient1->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, ExtractFileName(filePath)));

            std::unique_ptr<TFileStream> fStream = std::make_unique<TFileStream>(filePath, fmOpenRead);
            std::unique_ptr<TMemoryStream> mStream = std::make_unique<TMemoryStream>();

            CryptoUtils::encryptStreamRSA(codec.get(), signatory.get(), pubKeyPath, fStream.get(), mStream.get());

            IdTCPClient1->IOHandler->LargeStream = true;
            IdTCPClient1->IOHandler->Write(mStream.get(), 0, true);
            fStream.reset();
            mStream.reset();

            UnicodeString serverResponse = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, IdTCPClient1->IOHandler->ReadLn());

            if (serverResponse == "File converted") {

                UnicodeString convertedFilePath = FileUtils::traverseUpDirTree(filePath, 2) + "Data\\" + ExtractFileName(filePath);
                convertedFilePath = convertedFilePath.Delete(convertedFilePath.Length()-2, 3) + "json";

            	fStream = std::make_unique<TFileStream>(convertedFilePath, fmCreate);
                mStream = std::make_unique<TMemoryStream>();

                IdTCPClient1->IOHandler->LargeStream = true;
                IdTCPClient1->IOHandler->ReadStream(mStream.get());
                CryptoUtils::decryptStreamRSA(codec.get(), signatory.get(), prvKeyPath, fStream.get(), mStream.get());

                LOGGER(LogLevel::Debug, "Socket I/O complete");
                return true;
            }
       }
       catch (Exception &ex) {
            LOGGER(LogLevel::Error, "TCP client error: " + ex.Message);
        }

    }
    __finally {

    	IdTCPClient1->Disconnect();

    }
    return false;
}

