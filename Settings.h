//---------------------------------------------------------------------------

#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include<vcl.h>

class Settings {

    private:
        UnicodeString fontFamily;
        UnicodeString fontColor;
        int fontSize;

        UnicodeString separatorType;
        UnicodeString goalType;

        bool displayMistakes;
        bool displayAccuracy;
        bool displayTime;

    public:
        void setFontFamily(UnicodeString _fontFamily);
        void setFontColor(UnicodeString _fontColor);
        void setFontSize(int _fontSize);

};

#endif
