//---------------------------------------------------------------------------

#pragma hdrstop

#include "TimeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace TimeManager {

    UnicodeString getCurrentTime() {
        return FormatDateTime(L"hh:nn:ss", Now());
    }

    UnicodeString getCurrentDate() {
        return FormatDateTime(L"yyyy-mm-dd", Now());
    }

    UnicodeString getCurrentDateTime() {
        return FormatDateTime(L"yyyy-mm-dd hh:nn:ss", Now());
    }
}

