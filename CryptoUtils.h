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

	UnicodeString generateSHA512Hash(const UnicodeString& string);

    UnicodeString generateRandomSalt(int lengthBytes);
    UnicodeString byteToHex(unsigned char byte);

    std::unique_ptr<TCryptographicLibrary> createCryptoLib();
    std::unique_ptr<TSignatory>createSignatory();

    std::unique_ptr<TCodec> createAESCodec(TCryptographicLibrary *cryptoLibrary);
    std::unique_ptr<TCodec> createRSACodec(TCryptographicLibrary *cryptoLibrary);

   	bool generateRSAKeys(const UnicodeString &path, const UnicodeString &prvKeyName = "prv_key.bin", const UnicodeString &pubKeyName = "pub_key.bin");

    UnicodeString encryptStringAES(const UnicodeString &string);
    UnicodeString decryptStringAES(const UnicodeString &string);

    UnicodeString encryptStringRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, const UnicodeString &string);
    UnicodeString decryptStringRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, const UnicodeString &string);

    void encryptStreamRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, TStream *streamIn, TStream *streamOut);
    void decryptStreamRSA(TCodec *codec, TSignatory *signatory, const UnicodeString &path, TStream *streamIn, TStream *streamOut);




}

#endif
