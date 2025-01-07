//---------------------------------------------------------------------------

#pragma hdrstop

#include "AchievementsRecord.h"
#include <cwchar>
//---------------------------------------------------------------------------
#pragma package(smart_init)


int AchievementsRecord::idCounter = 1;

AchievementsRecord::AchievementsRecord() {}

AchievementsRecord::AchievementsRecord(int _idUser, const UnicodeString _title, const UnicodeString _description, TDateTime _date) : id(idCounter++), idUser(_idUser), date(_date) {

    wcsncpy_s(title, 30, _title.c_str(), 29);
    wcsncpy_s(description, 150, _description.c_str(), 149);
}

int AchievementsRecord::getIdUser() const {
    return idUser;
}

UnicodeString AchievementsRecord::getTitle() const {
    return UnicodeString(title);
}

UnicodeString AchievementsRecord::getDescription() const {
    return UnicodeString(description);
}

TDateTime AchievementsRecord::getDate() const {
    return date;
}


