//---------------------------------------------------------------------------


#pragma hdrstop

#include "DataModule.h"
#include "Generator.h"

#include "FileUtils.h"
#include "TextUtils.h"
#include "Logger.h"
#include "EFileNotFoundException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"

TDataModule2 *DataModule2;


__fastcall TDataModule2::TDataModule2(TComponent* Owner) : TDataModule(Owner) {

	LOGGER(LogLevel::Debug, "Created server");

}

void __fastcall TDataModule2::IdTCPServerExecute(TIdContext *AContext)
{
    TIdIOHandler *ioHandler = AContext->Connection->IOHandler;
    try {
    	try {

           	int requestType = StrToInt(ioHandler->ReadLn());

            if (requestType == 1) {
            	UnicodeString letters = ioHandler->ReadLn();
                bool useNumbers = StrToInt(ioHandler->ReadLn());
                bool useUppercase = StrToInt(ioHandler->ReadLn());
                bool usePunctuation = StrToInt(ioHandler->ReadLn());
                int min = StrToInt(ioHandler->ReadLn());
                int max = StrToInt(ioHandler->ReadLn());

                UnicodeString generatedText = Generator::generateText(letters, GeneratorOptions(useNumbers, useUppercase, usePunctuation, min, max));

            	ioHandler->WriteLn(generatedText);
            }
            else if (requestType == 2) {

                UnicodeString fileName = ioHandler->ReadLn();
                UnicodeString filePath = FileUtils::createAbsolutePath("Server\\Data\\srv_" + fileName, true);

                std::unique_ptr<TFileStream> fileStream = std::make_unique<TFileStream>(filePath, fmCreate);
                ioHandler->LargeStream = true;
                ioHandler->ReadStream(fileStream.get());
                fileStream.reset();

                std::optional<UnicodeString> buffer;

                try {
                    buffer = FileUtils::readFromTextFile(filePath);
                } catch (CustomExceptions::EFileNotFoundException &ex) {
                    LOGGER(LogLevel::Fatal, ex.getMessage());
                }

                if (buffer.has_value()) {
                    std::vector<UnicodeString> wordList = TextUtils::splitToTokens(*buffer);
                    std::optional<UnicodeString> jsonString = generateJsonFromWordList(wordList);

                    if (jsonString.has_value()) {

                    	UnicodeString convertedFilePath = FileUtils::createAbsolutePath("Server\\Data\\srv_" + fileName.Delete(fileName.Length()-2, 3) + "json", true);

                    	FileUtils::saveToTextFile(convertedFilePath, std::vector<UnicodeString>{*jsonString});
                        fileStream = std::make_unique<TFileStream>(filePath, fmOpenRead);

                    	ioHandler->WriteLn("File converted");
                        ioHandler->LargeStream = true;
                        ioHandler->Write(fileStream.get(), 0, true);
                    }
                }
            }

            LOGGER(LogLevel::Debug, "Server complete");

        }  catch (Exception &ex) {
        	LOGGER(LogLevel::Error, "Server error: " + ex.Message);
        }
    }__finally {
        AContext->Connection->Disconnect();
    }

}
//---------------------------------------------------------------------------

void __fastcall TDataModule2::IdTCPServerConnect(TIdContext *AContext)
{
	if (OnConnectionEstablished) {
        OnConnectionEstablished(this);
    }

    LOGGER(LogLevel::Debug, "Connection established.");
}
//---------------------------------------------------------------------------

void __fastcall TDataModule2::IdTCPServerDisconnect(TIdContext *AContext)
{
   	if (OnConnectionClosed) {
        OnConnectionClosed(this);
    }

    LOGGER(LogLevel::Debug, "Connection closed.");
}

std::optional<UnicodeString> TDataModule2::generateJsonFromWordList(const std::vector<UnicodeString> &wordList) {

	UnicodeString jsonString = "";

    TJSONObject *mainObject, *dictionaryEntryObject;
    TJSONArray *dictionaryArray, *synonymsArray;

    try {

        mainObject = new TJSONObject();
        try {
            dictionaryArray = new TJSONArray();

            mainObject->AddPair("dictionary", dictionaryArray);

            for (const UnicodeString& word: wordList) {

                if (!word.Length()) {
                    continue;
                }

                dictionaryEntryObject = new TJSONObject();
            	synonymsArray = new TJSONArray();
                synonymsArray->Add(UnicodeString(L""));

                dictionaryEntryObject->AddPair(new TJSONPair("word", word));
       			dictionaryEntryObject->AddPair(new TJSONPair("category", UnicodeString(L"")));
				dictionaryEntryObject->AddPair(new TJSONPair("definition", UnicodeString(L"")));
                dictionaryEntryObject->AddPair(new TJSONPair("synonyms", synonymsArray));

                dictionaryArray->AddElement(dictionaryEntryObject);
            }

        jsonString += TextUtils::formatJson(mainObject->ToString());
    	}
        __finally {
        	mainObject->Free();
    	}

    } catch (const Exception &ex) {
        LOGGER(LogLevel::Error, "Error converting to JSON");
    }

	if (!jsonString.IsEmpty()) {
		 return jsonString;
	}
	else {
		return std::nullopt;
    }

}

