//---------------------------------------------------------------------------

#ifndef EnumUtilsH
#define EnumUtilsH

#include <vector>
#include <vcl.h>
#include "Logger.h"

namespace EnumUtils  {

    template<typename T>
    T stringToEnum(const std::vector<UnicodeString> &enumStrings, const UnicodeString &string) {

        auto it = std::find(enumStrings.begin(), enumStrings.end(), string);
        if (it != enumStrings.end()) {

            return static_cast<T>(it - enumStrings.begin());

        } else {
            return T::Unknown;
        }
    }

    template<typename T>
    UnicodeString enumToString(const std::vector<UnicodeString> &enumStrings, T en) {

        int index = static_cast<int>(en);
        if (index >= 0 && index < enumStrings.size()) {
            return enumStrings[index];
        } else {
            return "Unknown";
        }
    }

};

#endif
