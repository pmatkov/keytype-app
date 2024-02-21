//---------------------------------------------------------------------------

#pragma hdrstop

#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void Settings::setFontFamily(UnicodeString _fontFamily) {
    fontFamily = _fontFamily;
}

void Settings::setFontColor(UnicodeString _fontColor) {
    fontColor = _fontColor;
}
void Settings::setFontSize(int _fontSize) {
    fontSize = _fontSize;
}
