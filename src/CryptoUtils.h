//---------------------------------------------------------------------------

#ifndef CryptoUtilsH
#define CryptoUtilsH

#include "uTPLb_BaseNonVisualComponent.hpp"
#include "uTPLb_Codec.hpp"
#include "uTPLb_CryptographicLibrary.hpp"
#include "uTPLb_Hash.hpp"
#include "uTPLb_Signatory.hpp"
#include "vcl.h"

#include <memory>
#include <vector>
//---------------------------------------------------------------------------

namespace CryptoUtils {

    UnicodeString generateSHA256Hash(const UnicodeString& string);
	UnicodeString generateSHA512Hash(const UnicodeString& string);

    UnicodeString generateRandomSalt(int lengthBytes);
    UnicodeString byteToHex(unsigned char byte);

    UnicodeString generateSalt(const UnicodeString& input);

    std::unique_ptr<TCryptographicLibrary> createCryptoLib();
    std::unique_ptr<TSignatory>createSignatory(TCodec *codec);

    std::unique_ptr<TCodec> createAESCodec(TCryptographicLibrary *cryptoLibrary);
    std::unique_ptr<TCodec> createRSACodec(TCryptographicLibrary *cryptoLibrary);

   	bool generateRSAKeys(const UnicodeString &path, const UnicodeString &prvKeyName = "prv_key.bin", const UnicodeString &pubKeyName = "pub_key.bin");

    UnicodeString encryptStringAES(const UnicodeString &string);
    UnicodeString decryptStringAES(const UnicodeString &string);

    UnicodeString encryptStringRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, const UnicodeString &string);
    UnicodeString decryptStringRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, const UnicodeString &string);

    void encryptStreamRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, TStream *streamIn, TStream *streamOut);
    void decryptStreamRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, TStream *streamIn, TStream *streamOut);

    UnicodeString createSignature(TSignatory *signatory, const UnicodeString &path, const UnicodeString &string, bool isToken);
    bool verifySignature(TSignatory *signatory, const UnicodeString &path, const UnicodeString &string, const UnicodeString &signature, bool isToken);

    UnicodeString encodeStringToBase64(const UnicodeString &string);
    UnicodeString decodeBase64ToString(const UnicodeString &b64string);
    UnicodeString encodeStringToBase64URL(const UnicodeString &string);
    UnicodeString decodeBase64URLToString(const UnicodeString &b64string);

    UnicodeString createToken(const UnicodeString& keyPath, const UnicodeString &username, const UnicodeString &role);
    bool verifyToken(const UnicodeString& keyPath, const UnicodeString &token);


}

#endif
