//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PreferencesForm.h"
#include "ENullPointerException.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFPreferences *FPreferences;
//---------------------------------------------------------------------------
__fastcall TFPreferences::TFPreferences(TComponent* Owner)	: TForm(Owner)  {}

__fastcall TFPreferences::TFPreferences(TComponent* Owner, MainSession *_mainSession)  : TForm(Owner)
{
    if (_mainSession) {
       mainSession = _mainSession;
       LOGGER(LogLevel::Debug, "Preferences created");
    }
    else {
        throw ENullPointerException();
    }
}
//---------------------------------------------------------------------------

