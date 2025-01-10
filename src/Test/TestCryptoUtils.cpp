//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <memory>

#include "FileUtils.h"
#include "TextUtils.h"
#include "CryptoUtils.h"
#include "AchievementsHeader.h"
#include "Random.h"

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
      void __fastcall TestgenerateSalt();
      void __fastcall TestgeneratePasswordHash();
      void __fastcall TestverifyPasswordHash();
      void __fastcall TeststringEncryptionAES();
      void __fastcall TestgenerateRSAKeys();
      void __fastcall TeststringEncryptionRSA();
      void __fastcall TestdigitalSignatureString();
      void __fastcall TestB64Encoding();
      void __fastcall TesttokenAuthentication();
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

}

void __fastcall TTestCryptoUtils::TestgenerateRandomSalt()
{
    UnicodeString result = CryptoUtils::generateRandomSalt(32);

	LOGGER_LOG("Result p1: " + result.SubString(1,32));
    LOGGER_LOG("Result p2: " + result.SubString(32,32));
}

void __fastcall TTestCryptoUtils::TestgenerateSalt()
{
    UnicodeString result = CryptoUtils::generateSalt("user");

	LOGGER_LOG("Result: " + result);
}

void __fastcall TTestCryptoUtils::TestgeneratePasswordHash()
{

    UnicodeString salt = CryptoUtils::generateSalt("admin");
    UnicodeString hashedSalt = CryptoUtils::generateSHA256Hash(salt);
    UnicodeString result = CryptoUtils::generateSHA512Hash(UnicodeString(Random::getRandom(1, 100)) + "123" + hashedSalt);

	LOGGER_LOG("Result: " + result);
}

void __fastcall TTestCryptoUtils::TestverifyPasswordHash()
{
    bool verified = false;
    UnicodeString salt = CryptoUtils::generateSalt("user");
    UnicodeString hashedSalt = CryptoUtils::generateSHA256Hash(salt);
    UnicodeString hashedPassword = "DB2C55FA1259A63BEEF8E2FDB3690C0F8665538A8B796A13B9B8C297F1E4E4A1DEACEEFEEC9694F559EE2D499568BBC2D60AB9CD2A8F0972DABFDFB1943783E2";

    for (int i = 1; i <= 100; i++) {

      if (CryptoUtils::generateSHA512Hash(IntToStr(i) + "123" + hashedSalt) == hashedPassword) {
          verified = true;
          break;
      }
    }
	LOGGER_LOG("Result: " + UnicodeString(verified ? "passed" : "failed"));
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
	bool resultOk = CryptoUtils::generateRSAKeys(FileUtils::createProjectSubDirPath("Keys"));

	LOGGER_LOG("Keys " + UnicodeString(resultOk ? "were" : "were not") + "generated");

    CheckEquals(true, resultOk);
}

void __fastcall TTestCryptoUtils::TeststringEncryptionRSA() {

    std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
    std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
    std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

	UnicodeString pubKeyPath = FileUtils::createProjectSubDirPath("Keys") + "pub_key.bin";
	UnicodeString prvKeyPath = FileUtils::createProjectSubDirPath("Keys") + "prv_key.bin";
	UnicodeString inputString = "2";

	UnicodeString encrytpedString = CryptoUtils::encryptStringRSA(codec.get(), signatory.get(), pubKeyPath, inputString);
    UnicodeString decrytpedString = CryptoUtils::decryptStringRSA(codec.get(), signatory.get(), prvKeyPath, encrytpedString);

	LOGGER_LOG("Input: " + inputString + " Encrpyted: " + encrytpedString + " Decrpyted: " + decrytpedString);
    CheckEquals(inputString, decrytpedString);

}

void __fastcall TTestCryptoUtils::TestdigitalSignatureString() {

    std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
    std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
    std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

	UnicodeString pubKeyPath = FileUtils::createProjectSubDirPath("Keys") + "pub_key.bin";
	UnicodeString prvKeyPath = FileUtils::createProjectSubDirPath("Keys") + "prv_key.bin";
	UnicodeString inputString = "digital signature";
    UnicodeString invalidtring = "digitalsignature";

	UnicodeString signature = CryptoUtils::createSignature(signatory.get(), prvKeyPath, inputString, false);
    LOGGER_LOG("Input: " + inputString + " Signature: " + signature);

    bool signatureVerified = CryptoUtils::verifySignature(signatory.get(), pubKeyPath, inputString, signature, true);
    CheckEquals(true, signatureVerified);

    signatureVerified = CryptoUtils::verifySignature(signatory.get(), pubKeyPath, invalidtring, signature, false);
    CheckEquals(false, signatureVerified);
}


void __fastcall TTestCryptoUtils::TestB64Encoding() {

	UnicodeString inputString = "pozo izquierdo";
    UnicodeString b64encoded, b64decoded;

    b64encoded = CryptoUtils::encodeStringToBase64(inputString);
    LOGGER_LOG("Input: " + inputString + " B64 string: " + b64encoded);

    b64decoded = CryptoUtils::decodeBase64ToString(b64encoded);
    LOGGER_LOG("B64 string: " + b64encoded + " Output: " + b64decoded);
    CheckEquals(b64decoded, inputString);
}

void __fastcall TTestCryptoUtils::TesttokenAuthentication() {

	UnicodeString pubKeyPath = FileUtils::createProjectSubDirPath("Keys") + "pub_key.bin";
	UnicodeString prvKeyPath = FileUtils::createProjectSubDirPath("Keys") + "prv_key.bin";

    UnicodeString token = CryptoUtils::createToken(prvKeyPath, "thomas", "regular");
    LOGGER_LOG("Token: " + token);

    bool tokenVerified = CryptoUtils::verifyToken(pubKeyPath, token);
    CheckEquals(true, tokenVerified);

    std::vector<UnicodeString> tokens = TextUtils::splitToTokens(token, '.');
    UnicodeString decodedPayload = CryptoUtils::decodeBase64URLToString(tokens[1]);

    std::unique_ptr<TJSONValue> jsonValue(TJSONObject::ParseJSONValue(decodedPayload));
    TJSONObject *jsonPayload = static_cast<TJSONObject*>(jsonValue.get());

    UnicodeString role = "";

    if (jsonPayload->Values["role"]) {
        role = TextUtils::trimCharacters(jsonPayload->Values["role"]->ToString(), L'\"');
    }
    LOGGER_LOG("Role: " + role);
    CheckEquals("regular", role);
}


static void registerTests()
{
  Testframework::RegisterTest(TTestCryptoUtils::Suite());
}
#pragma startup registerTests 33
