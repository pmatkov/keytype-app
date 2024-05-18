//---------------------------------------------------------------------------

#ifndef AchievementsRecordH
#define AchievementsRecordH
//---------------------------------------------------------------------------
#include "vcl.h"

class AchievementsRecord {

    private:
        int id;
        int idUser;
        wchar_t title[30];
        wchar_t description[150];
        TDateTime date;

        static int idCounter;

    public:
        AchievementsRecord();
        AchievementsRecord(int _idUser, const UnicodeString _title, const UnicodeString _badge, TDateTime _date);

        int getIdUser() const;
        UnicodeString getTitle() const;
        UnicodeString getDescription() const;
        TDateTime getDate() const;

        operator UnicodeString() const {
            return L"id: " + IntToStr(id) + L" idUser: " + IntToStr(idUser) + L" title: " + UnicodeString(title) \
             + L" description: " + UnicodeString(description) + L" date: " + FormatDateTime("dd/mm/yyyy", date);
        }


};

#endif
