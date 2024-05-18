//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <memory>

#include "CryptoUtils.h"
#include "FileUtils.h"
#include "AchievementsHeader.h"

#include "UnitTestLogger.h"

class TTestCryptoUtils : public TTestCase
{
public:
	  __fastcall virtual TTestCryptoUtils(System::String name) : TTestCase(name) {}
	  virtual void __fastcall SetUp();
	  virtual void __fastcall TearDown();

__published:
	  void __fastcall TestgenerateSHA512Hash();
      void __fastcall TestgenerateRandomSalt();
      void __fastcall TeststringEncryptionAES();
      void __fastcall TestgenerateRSAKeys();
      void __fastcall TeststringEncryptionRSA();
};


void __fastcall TTestCryptoUtils::SetUp()
{
    LOGGER_CLEAR_LOG();
	LOGGER_LOG("Starting test...");
}

void __fastcall TTestCryptoUtils::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}

void __fastcall TTestCryptoUtils::TestgenerateSHA512Hash()
{

    AchievementsHeader header("ACHFile", 1.0, 2);
    UnicodeString hash = CryptoUtils::generateSHA512Hash(UnicodeString(header));
    header.setHashValue(hash);

    UnicodeString result = CryptoUtils::generateSHA512Hash(header);

	LOGGER_LOG("Input: " + UnicodeString(header) + " Result: " + result);
    CheckEquals(hash, result);

//    result = CryptoUtils::generateSHA512Hash("123"+ UnicodeString("B94154386BB7B86C3B9D574E7500FECBE04564E42FAB1DE7036AB2C109F4E942"));
//
//	LOGGER_LOG("Result: " + result);
}

void __fastcall TTestCryptoUtils::TestgenerateRandomSalt()
{

    UnicodeString result = CryptoUtils::generateRandomSalt(32);

	LOGGER_LOG("Result p1: " + result.SubString(1,32));
    LOGGER_LOG("Result p2: " + result.SubString(32,32));
}

void __fastcall TTestCryptoUtils::TeststringEncryptionAES()
{
    UnicodeString inputString = "Windsurfing";
	UnicodeString encrytpedString = CryptoUtils::encryptStringAES(inputString);
    UnicodeString decrytpedString = CryptoUtils::decryptStringAES(encrytpedString);

	LOGGER_LOG("Input: " + inputString + " Encrpyted: " + encrytpedString + " Decrpyted: " + decrytpedString);
    CheckEquals(inputString, decrytpedString);
}

void __fastcall TTestCryptoUtils::TestgenerateRSAKeys()
{
	bool resultOk = CryptoUtils::generateRSAKeys(FileUtils::createAbsolutePath("Keys", false));

    LOGGER_LOG("Keys " + UnicodeString(resultOk ? "were" : "were not") + "generated");

    CheckEquals(true, resultOk);
}

void __fastcall TTestCryptoUtils::TeststringEncryptionRSA() {

    std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
    std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
    std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory();
    signatory->Codec = codec.get();

    UnicodeString pubKeyPath = FileUtils::createAbsolutePath("Keys\\pub_key_srv.bin", true);
    UnicodeString prvKeyPath = FileUtils::createAbsolutePath("Keys\\prv_key_srv.bin", true);
	UnicodeString inputString = "2";

	UnicodeString encrytpedString = CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, inputString);
    UnicodeString decrytpedString = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, encrytpedString);

	LOGGER_LOG("Input: " + inputString + " Encrpyted: " + encrytpedString + " Decrpyted: " + decrytpedString);
    CheckEquals(inputString, decrytpedString);

}

static void registerTests()
{
  Testframework::RegisterTest(TTestCryptoUtils::Suite());
}
#pragma startup registerTests 33
