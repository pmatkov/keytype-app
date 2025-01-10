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
__fastcall TDataModule1::TDataModule1(TComponent* Owner) : TDataModule(Owner)  {}


// avgChars = charCount/ wordCount (TLessons)

void __fastcall TDataModule1::TLessonsCalcFields(TDataSet *DataSet)
{
 	if (DataSet->State != dsInsert && DataSet->State != dsEdit) {
       float avgChar = static_cast<float>(TLessons->FieldByName("charCount")->AsInteger) / TLessons->FieldByName("wordCount")->AsInteger;
       TLessons->FieldByName("avgChars")->AsFloat = RoundTo(avgChar, -2);
    }
}

// durationHMS = seconds to hh:mm:ss (TLessonResults)

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


// text generation - TCP client + RSA encryption

UnicodeString TDataModule1::generateText(const UnicodeString &letters, bool useNumbers, bool useUppercase,  bool usePunctuation, int minTokens, int maxTokens) {

    UnicodeString generatedText = "";

    try {
       try {

       		std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
			std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
			std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

			UnicodeString prvKeyPath = FileUtils::createProjectSubDirPath("Keys") + "prv_key_app.bin";
			UnicodeString pubKeyPath = FileUtils::createProjectSubDirPath("Keys") + "pub_key_srv.bin";

            IdTCPClient->Connect();

			LOGGER(LogLevel::Debug, "Connected to TCP server");

			IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, "1"));
            IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, letters));
            IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(useNumbers)));
            IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(useUppercase)));
            IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(usePunctuation)));
            IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(minTokens)));
            IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, UnicodeString(maxTokens)));

            generatedText = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, IdTCPClient->IOHandler->ReadLn());

            LOGGER(LogLevel::Debug, "TCP I/O complete");
       }
       catch (Exception &ex) {
            LOGGER(LogLevel::Error, "TCP client error: " + ex.Message);
        }

    }
    __finally {

    	IdTCPClient->Disconnect();

    }
    return generatedText;
}

// file conversion - TCP client + RSA encryption (streams)

bool TDataModule1::convertWordList(const UnicodeString& filePath) {

    try {
    	try {

        	std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
            std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
            std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

			UnicodeString prvKeyPath = FileUtils::createProjectSubDirPath("Keys") + "prv_key_app.bin";
			UnicodeString pubKeyPath = FileUtils::createProjectSubDirPath("Keys") + "pub_key_srv.bin";

            IdTCPClient->Connect();

			LOGGER(LogLevel::Debug, "Connected to TCP server");

			IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, "2"));
            IdTCPClient->IOHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, ExtractFileName(filePath)));

            std::unique_ptr<TFileStream> fStream = std::make_unique<TFileStream>(filePath, fmOpenRead);
            std::unique_ptr<TMemoryStream> mStream = std::make_unique<TMemoryStream>();

            CryptoUtils::encryptStreamRSA(codec.get(), signatory.get(), pubKeyPath, fStream.get(), mStream.get());

			// send stream size using Write(Int64) before sending stream data (largeStream)
            IdTCPClient->IOHandler->LargeStream = true;
            IdTCPClient->IOHandler->Write(mStream.get(), 0, true);
            fStream.reset();
            mStream.reset();

            UnicodeString serverResponse = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, IdTCPClient->IOHandler->ReadLn());

            if (serverResponse == "File converted") {

				UnicodeString convertedFilePath = FileUtils::createStepUpDirPath(filePath, 2) + "Data\\" + ExtractFileName(filePath);
				convertedFilePath = convertedFilePath.Delete(convertedFilePath.Length()-2, 3) + "json";

            	fStream = std::make_unique<TFileStream>(convertedFilePath, fmCreate);
                mStream = std::make_unique<TMemoryStream>();

                IdTCPClient->IOHandler->LargeStream = true;
                IdTCPClient->IOHandler->ReadStream(mStream.get());
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

    	IdTCPClient->Disconnect();

    }
    return false;
}

UnicodeString TDataModule1::translateKey(const UnicodeString &key) {

    UnicodeString translatedKey = "";

    try {
        IdUDPClient->Send(key);
        translatedKey = IdUDPClient->ReceiveString();

        LOGGER(LogLevel::Debug, "UDP I/O complete");
    }
    catch (Exception &ex) {
    	LOGGER(LogLevel::Error, "UDP client error: " + ex.Message);
    }

    return translatedKey;
}


