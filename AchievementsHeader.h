//---------------------------------------------------------------------------

#ifndef AchievementsHeaderH
#define AchievementsHeaderH
//---------------------------------------------------------------------------
#include <vcl.h>

class AchievementsHeader {

    private:
        wchar_t signature[10];
        float version;
		wchar_t hash[128+1];
        int recordCount;

    public:
         AchievementsHeader();
         AchievementsHeader(UnicodeString _signature, float _version, int _recordCount);

         void setHashValue(const UnicodeString _hash);
         UnicodeString getHashValue() const;

         void setRecordCount(int _recordCount);
         int getRecordCount() const;

         operator UnicodeString() const {
            return L"signature: " + UnicodeString(signature) + L" version: " + FormatFloat("0.00", version) + L" record count: " + IntToStr(recordCount);
        }
};

#endif
