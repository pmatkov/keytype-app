//---------------------------------------------------------------------------

#pragma hdrstop

#include "AchievementsHeader.h"
#include "CryptoUtils.h"
#include <cwchar>

//---------------------------------------------------------------------------
#pragma package(smart_init)

AchievementsHeader::AchievementsHeader() {}

AchievementsHeader::AchievementsHeader(UnicodeString _signature, float _version, int _recordCount) : version(_version), recordCount (_recordCount)  {

   wcsncpy_s(signature, 10, _signature.c_str(), 9);
}

 UnicodeString AchievementsHeader::getHashValue() const {

	return UnicodeString(hash);
 }

 void AchievementsHeader::setHashValue(const UnicodeString _hash) {

 	wcsncpy_s(hash, 128+1, _hash.c_str(), 128);
 }

 int AchievementsHeader::getRecordCount() const {
      return recordCount;
 }

 void AchievementsHeader::setRecordCount(int _recordCount) {
    recordCount = _recordCount;
 }
