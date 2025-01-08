//---------------------------------------------------------------------------


#pragma hdrstop

#include <map>

#include "DataModule.h"
#include "Generator.h"

#include "FileUtils.h"
#include "TextUtils.h"
#include "CryptoUtils.h"
#include "Logger.h"
#include "EFileNotFoundException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"

TDataModule2 *DataModule2;


__fastcall TDataModule2::TDataModule2(TComponent* Owner) : TDataModule(Owner) {}

void __fastcall TDataModule2::IdTCPServerExecute(TIdContext *AContext)
{
    TIdIOHandler *ioHandler = AContext->Connection->IOHandler;

    try {
    	try {

        	std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
            std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
            std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

        	UnicodeString prvKeyPath = FileUtils::createAbsolutePath("Server\\Keys\\prv_key_srv.bin", true);
            UnicodeString pubKeyPath = FileUtils::createAbsolutePath("Server\\Keys\\pub_key_app.bin", true);

            int requestType = StrToInt(CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn()));

            // text generation - TCP server + RSA encryption

            if (requestType == 1) {

            	UnicodeString letters = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn());
                bool useNumbers = StrToInt(CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn()));
                bool useUppercase = StrToInt(CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn()));
                bool usePunctuation = StrToInt(CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn()));
                int minTokens = StrToInt(CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn()));
                int maxTokens = StrToInt(CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn()));

                Generator generator(letters, useNumbers, useUppercase, usePunctuation);
                UnicodeString generatedText = generator.generateTokenSequence(3, 8, minTokens, maxTokens);

                ioHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, generatedText));

            }

            // file conversion - TCP server + RSA encryption (streams)

            else if (requestType == 2) {

                UnicodeString fileName = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, ioHandler->ReadLn());

                UnicodeString filePath = FileUtils::createAbsolutePath("Server\\Data\\srv_" + fileName, true);

                std::unique_ptr<TFileStream> fStream = std::make_unique<TFileStream>(filePath, fmCreate);
                std::unique_ptr<TMemoryStream> mStream = std::make_unique<TMemoryStream>();

                ioHandler->LargeStream = true;
                ioHandler->ReadStream(mStream.get());
            	CryptoUtils::decryptStreamRSA(codec.get(), signatory.get(), prvKeyPath, fStream.get(), mStream.get());

                fStream.reset();
                mStream.reset();

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

                        ioHandler->WriteLn(CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, "File converted"));

                        fStream = std::make_unique<TFileStream>(convertedFilePath, fmOpenRead);
                        mStream = std::make_unique<TMemoryStream>();

                        CryptoUtils::encryptStreamRSA(codec.get(), signatory.get(), pubKeyPath, fStream.get(), mStream.get());

                        ioHandler->LargeStream = true;
                        ioHandler->Write(mStream.get(), 0, true);

                    }
                }
            }

            LOGGER(LogLevel::Debug, "Socket I/O complete");

        }  catch (Exception &ex) {
        	LOGGER(LogLevel::Error, "TCP server error: " + ex.Message);
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

    LOGGER(LogLevel::Debug, "Connection established");
}
//---------------------------------------------------------------------------

void __fastcall TDataModule2::IdTCPServerDisconnect(TIdContext *AContext)
{
   	if (OnConnectionClosed) {
        OnConnectionClosed(this);
    }

    LOGGER(LogLevel::Debug, "Connection closed");
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

void __fastcall TDataModule2::IdUDPServerUDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData, TIdSocketHandle *ABinding)
{
    std::map<wchar_t, wchar_t> qwertzToDvorak = {
        {'Q', '\''}, {'W', ','}, {'E', '.'}, {'R', 'P'}, {'T', 'Y'},
        {'Y', 'F'}, {'U', 'G'}, {'I', 'C'}, {'O', 'R'}, {'P', 'L'},
        {'A', 'A'}, {'S', 'O'}, {'D', 'E'}, {'F', 'U'}, {'G', 'I'},
        {'H', 'D'}, {'J', 'H'}, {'K', 'T'}, {'L', 'N'}, {';', 'S'},
       	{'\'', '-'}, {'Z', ';'}, {'X', 'Q'}, {'C', 'J'}, {'V', 'K'},
        {'B', 'X'}, {'N', 'B'}, {'M', 'M'}, {',', 'W'}, {'.', 'V'},
        {'/', 'Z'},
    };

	UnicodeString key = TEncoding::UTF8->GetString(AData);
    UnicodeString translatedKey = key;

    if (key.Length() == 1) {

        std::map<wchar_t, wchar_t>::iterator it = qwertzToDvorak.find(key[1]);

       if (it != qwertzToDvorak.end()) {
       		translatedKey = it->second;
       }

    }

    ABinding->SendTo(ABinding->PeerIP, ABinding->PeerPort, translatedKey);
}
//---------------------------------------------------------------------------

