//---------------------------------------------------------------------------

#ifndef AchievementsHeaderH
#define AchievementsHeaderH
//---------------------------------------------------------------------------
#include <vcl.h>

class AchievementsHeader {

    private:
        wchar_t signature[10];
        float version;
        int recordCount;

        wchar_t hash[128+1];

    public:
         AchievementsHeader();
         AchievementsHeader(UnicodeString _signature, float _version, int _recordCount);

         UnicodeString getHashValue() const;
         void setHashValue(const UnicodeString _hash);

         int getRecordCount() const;
         void setRecordCount(int _recordCount);

         operator UnicodeString() const {
            return L"signature: " + UnicodeString(signature) + L" version: " + FormatFloat("0.00", version) + L" record count: " + IntToStr(recordCount);
        }
};

#endif
