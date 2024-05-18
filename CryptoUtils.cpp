//---------------------------------------------------------------------------

#pragma hdrstop

#include "CryptoUtils.h"
#include "FileUtils.h"
#include <bcrypt.h>
#include <ntstatus.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "bcrypt.lib"

namespace CryptoUtils {


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


    std::unique_ptr<TSignatory> createSignatory() {
          return std::make_unique<TSignatory>(nullptr);
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
        std::unique_ptr<TSignatory> signatory = CryptoUtils::createSignatory();
        signatory->Codec = codec.get();

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



}
