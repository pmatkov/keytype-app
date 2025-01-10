//---------------------------------------------------------------------------

#pragma hdrstop

#include "CryptoUtils.h"
#include "FileUtils.h"
#include "TextUtils.h"

#include <bcrypt.h>
#include <ntstatus.h>
#include <System.NetEncoding.hpp>
#include <System.DateUtils.hpp>
#include <System.JSON.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "bcrypt.lib"

namespace CryptoUtils {

    UnicodeString generateSHA256Hash(const UnicodeString& string) {

    	std::unique_ptr<THash> hash = std::make_unique<THash>(nullptr);
        std::unique_ptr<TCryptographicLibrary> cryptoLibrary = std::make_unique<TCryptographicLibrary>(nullptr);

        hash->CryptoLibrary = cryptoLibrary.get();
        hash->HashId = "native.hash.SHA-256";
        hash->HashString(string, TEncoding::UTF8);

        return Stream_To_Hex(hash->HashOutputValue);
    }

    UnicodeString generateSHA512Hash(const UnicodeString& string) {

    	std::unique_ptr<THash> hash = std::make_unique<THash>(nullptr);
        std::unique_ptr<TCryptographicLibrary> cryptoLibrary = std::make_unique<TCryptographicLibrary>(nullptr);

        hash->CryptoLibrary = cryptoLibrary.get();
        hash->HashId = "native.hash.SHA-512";
        hash->HashString(string, TEncoding::UTF8);

        return Stream_To_Hex(hash->HashOutputValue);
    }

    UnicodeString generateRandomSalt(int lengthBytes) {

     	std::vector<unsigned char> salt(lengthBytes);
        UnicodeString saltHex = "";

        NTSTATUS status = BCryptGenRandom(
            nullptr,
            salt.data(),
            static_cast<ULONG>(salt.size()),
            BCRYPT_USE_SYSTEM_PREFERRED_RNG
        );

        if (status) {
            return "";
        }

        for (unsigned char byte: salt) {
            saltHex += byteToHex(byte);
        }

        return saltHex;
    }

    UnicodeString generateSalt(const UnicodeString& input) {

        UnicodeString salt;
        int ascii_sum = 0;
        for (char c : input) {
            ascii_sum += static_cast<int>(c);
        }
        ascii_sum %= 26;
        for (char c : input) {
            if (isalpha(c)) {
                char base = static_cast<int>(c) % 2 == 0 ? 'a' : 'A';
                c = base + (c - base + ascii_sum) % 26;
            }
            salt += c;
        }
        return salt;
    }

    UnicodeString byteToHex(unsigned char byte) {

        UnicodeString hexChars = "0123456789ABCDEF";
        UnicodeString hexByte = "";

       	hexByte += hexChars[byte / 16 + 1];
        hexByte += hexChars[byte % 16 + 1];

        return hexByte;
    }

    std::unique_ptr<TCryptographicLibrary> createCryptoLib() {
          return std::make_unique<TCryptographicLibrary>(nullptr);
    }


    std::unique_ptr<TSignatory> createSignatory(TCodec *codec) {

    	std::unique_ptr<TSignatory> signatory = std::make_unique<TSignatory>(nullptr);
        signatory->Codec = codec;

        return signatory;
    }

    std::unique_ptr<TCodec> createAESCodec(TCryptographicLibrary *cryptoLibrary) {
    	std::unique_ptr<TCodec> codec = std::make_unique<TCodec>(nullptr);

        codec->CryptoLibrary = cryptoLibrary;
        codec->BlockCipherId = "native.AES-256";
        codec->StreamCipherId = "native.StreamToBlock";
        codec->ChainModeId = "native.CBC";
        codec->Password = "8f92w3x5NhG7kL8pWqZ0XzC1MvT9dR2bQyJ4K6sE7AaL1V3PqF8YgH6NrJ2UcX5W";

        return codec;
    }


    std::unique_ptr<TCodec> createRSACodec(TCryptographicLibrary *cryptoLibrary) {
    	std::unique_ptr<TCodec> codec = std::make_unique<TCodec>(nullptr);

        codec->CryptoLibrary = cryptoLibrary;
        codec->StreamCipherId = "native.RSA";
        codec->ChainModeId = "native.CBC";
        codec->AsymetricKeySizeInBits = 1024;
        codec->Password = "";

        return codec;
    }


    bool generateRSAKeys(const UnicodeString &path, const UnicodeString &prvKeyName, const UnicodeString &pubKeyName) {

    	std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
        std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
        std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

        std::unique_ptr<TFileStream> privateFstream = std::make_unique<TFileStream>(path + prvKeyName, fmCreate);
        std::unique_ptr<TFileStream> publicFstream = std::make_unique<TFileStream>(path + pubKeyName, fmCreate);

        if (signatory->GenerateKeys()) {

      		signatory->StoreKeysToStream(privateFstream.get(), TKeyStoragePartSet() << partPrivate);
            signatory->StoreKeysToStream(publicFstream.get(), TKeyStoragePartSet() << partPublic);

            return true;
        }
        return false;
    }


    UnicodeString encryptStringAES(const UnicodeString &string) {

    	std::unique_ptr<TCryptographicLibrary> cryptoLibrary = createCryptoLib();
        std::unique_ptr<TCodec> codec = createAESCodec(cryptoLibrary.get());

        UnicodeString encryptedString;

        codec->EncryptString(string, encryptedString, TEncoding::UTF8);

        return encryptedString;
    }

    UnicodeString decryptStringAES(const UnicodeString &string) {

    	std::unique_ptr<TCryptographicLibrary> cryptoLibrary = createCryptoLib();
        std::unique_ptr<TCodec> codec = createAESCodec(cryptoLibrary.get());

        UnicodeString decryptedString;

        codec->DecryptString(decryptedString, string, TEncoding::UTF8);

        return decryptedString;
    }

    UnicodeString encryptStringRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, const UnicodeString &string) {

        std::unique_ptr<TFileStream> pukFstream;

        UnicodeString encryptedString = "";

    	if (FileExists(path)) {
        	pukFstream = std::make_unique<TFileStream>(path, fmOpenRead);
            signatory->LoadKeysFromStream(pukFstream.get(), TKeyStoragePartSet() << partPublic);
            codec->EncryptString(string, encryptedString, TEncoding::UTF8);
        }

        return encryptedString;
    }

    UnicodeString decryptStringRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, const UnicodeString &string) {

        std::unique_ptr<TFileStream> prkFstream;

        UnicodeString decryptedString = "";

    	if (FileExists(path)) {
        	prkFstream = std::make_unique<TFileStream>(path, fmOpenRead);
            signatory->LoadKeysFromStream(prkFstream.get(), TKeyStoragePartSet() << partPrivate);
        	codec->DecryptString(decryptedString, string, TEncoding::UTF8);
        }

        return decryptedString;
    }

    void encryptStreamRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, TStream *streamIn, TStream *streamOut) {

        std::unique_ptr<TFileStream> pukFstream;

    	if (FileExists(path)) {
        	pukFstream = std::make_unique<TFileStream>(path, fmOpenRead);
            signatory->LoadKeysFromStream(pukFstream.get(), TKeyStoragePartSet() << partPublic);
            codec->EncryptStream(streamIn, streamOut);
        }

    }

    void decryptStreamRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, TStream *streamIn, TStream *streamOut) {

        std::unique_ptr<TFileStream> prkFstream;

    	if (FileExists(path)) {
        	prkFstream = std::make_unique<TFileStream>(path, fmOpenRead);
            signatory->LoadKeysFromStream(prkFstream.get(), TKeyStoragePartSet() << partPrivate);
        	codec->DecryptStream(streamIn, streamOut);
        }

    }

    UnicodeString createSignature(TSignatory *signatory, const UnicodeString &path, const UnicodeString &string, bool isToken) {

        std::unique_ptr<TFileStream> prkFstream;
        UnicodeString signedString;

    	if (FileExists(path)) {
        	prkFstream = std::make_unique<TFileStream>(path, fmOpenRead);
            signatory->LoadKeysFromStream(prkFstream.get(), TKeyStoragePartSet() << partPrivate);

            std::unique_ptr<TStringStream> stringStream;

            if (!isToken) {
            	stringStream = std::make_unique<TStringStream>(string);

            }
            else {

                std::vector<UnicodeString> tokens = TextUtils::splitToTokens(string, '.');
               	UnicodeString t1 = decodeBase64URLToString(tokens[0]);
               	UnicodeString t2 = decodeBase64URLToString(tokens[1]);

                stringStream = std::make_unique<TStringStream>(t1 + "." + t2);
            }
            std::unique_ptr<TStringStream> signatureStream = std::make_unique<TStringStream>();

            signatory->Sign(stringStream.get(), signatureStream.get());
            signedString = signatureStream->DataString;
        }
        return signedString;
    }

    bool verifySignature(TSignatory *signatory, const UnicodeString &path, const UnicodeString &string, const UnicodeString &signature, bool isToken)  {

    	std::unique_ptr<TFileStream> pukFstream;
        TVerifyResult result;

    	if (FileExists(path)) {
        	pukFstream = std::make_unique<TFileStream>(path, fmOpenRead);
            signatory->LoadKeysFromStream(pukFstream.get(), TKeyStoragePartSet() << partPublic);

            std::unique_ptr<TStringStream> stringStream, signatureStream;

            if (!isToken) {
            	stringStream = std::make_unique<TStringStream>(string);
                signatureStream = std::make_unique<TStringStream>(signature);
            }
            else {
                std::vector<UnicodeString> tokens = TextUtils::splitToTokens(string, '.');
               	UnicodeString t1 = decodeBase64URLToString(tokens[0]);
               	UnicodeString t2 = decodeBase64URLToString(tokens[1]);
                UnicodeString t3 = decodeBase64URLToString(signature);

                stringStream = std::make_unique<TStringStream>(t1 + "." + t2);
                signatureStream = std::make_unique<TStringStream>(t3);
            }

            result = signatory->Verify(stringStream.get(), signatureStream.get());
        }

        return vPass == result;
    }

    UnicodeString encodeStringToBase64(const UnicodeString &string) {

         TBytes bytes = TEncoding::UTF8->GetBytes(string);

         return TNetEncoding::Base64->EncodeBytesToString(bytes.data(), bytes.Length - 1);
    }

    UnicodeString decodeBase64ToString(const UnicodeString &b64string) {

         TBytes bytes = TNetEncoding::Base64->DecodeStringToBytes(b64string);

         return TEncoding::UTF8->GetString(bytes);
    }

    UnicodeString encodeStringToBase64URL(const UnicodeString &string) {

         TBytes bytes = TEncoding::UTF8->GetBytes(string);

         return TNetEncoding::Base64URL->EncodeBytesToString(bytes.data(), bytes.Length - 1);
    }

    UnicodeString decodeBase64URLToString(const UnicodeString &b64string) {

         TBytes bytes = TNetEncoding::Base64URL->DecodeStringToBytes(b64string);

         return TEncoding::UTF8->GetString(bytes);
    }

    UnicodeString createToken(const UnicodeString& keyPath, const UnicodeString &username, const UnicodeString &role) {

        std::unique_ptr<TJSONObject> header = std::make_unique<TJSONObject>();
        header->AddPair("alg", "RSA");
        header->AddPair("typ", "JWT");
        UnicodeString base64Header = CryptoUtils::encodeStringToBase64URL(header->ToString());

        std::unique_ptr<TJSONObject> payload = std::make_unique<TJSONObject>();
        payload->AddPair("sub", username);
        payload->AddPair("role", role);
        payload->AddPair("iat", IntToStr(DateTimeToUnix(Now())));
        UnicodeString base64Payload = CryptoUtils::encodeStringToBase64URL(payload->ToString());

        std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
        std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
        std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

        UnicodeString signature = CryptoUtils::createSignature(signatory.get(), keyPath, base64Header + "." + base64Payload, true);
        UnicodeString base64Signature = CryptoUtils::encodeStringToBase64URL(signature);

        return base64Header + "." +  base64Payload + "." +  base64Signature;

    }

    bool verifyToken(const UnicodeString& keyPath, const UnicodeString &token) {

        std::vector<UnicodeString> tokens = TextUtils::splitToTokens(token, '.');

        if (tokens.size() != 3) {
           return false;
        }

        std::unique_ptr<TCryptographicLibrary> cryptLib = CryptoUtils::createCryptoLib();
        std::unique_ptr<TCodec> codec = CryptoUtils::createRSACodec(cryptLib.get());
        std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory(codec.get());

        return CryptoUtils::verifySignature(signatory.get(), keyPath, tokens[0] + "." + tokens[1], tokens[2], true);
    }

}
