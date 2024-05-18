//---------------------------------------------------------------------------
#undef UNICODE
#define UNICODE

#include <vcl.h>
#include <memory>
#pragma hdrstop

#include "MainFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrMain *FrMain;
//---------------------------------------------------------------------------
__fastcall TFrMain::TFrMain(TComponent* Owner) : TFrame(Owner) {

    HINSTANCE Resource;

    if ((Resource = LoadLibrary(L"ResourceLib.dll")) == nullptr) {
        ShowMessage("Can't load DLL");
        return;
    }

    std::unique_ptr<TResourceStream> resStream = std::make_unique<TResourceStream>((int)Resource, 1, RT_FONT);

    DWORD FontsCount;
    if (!AddFontMemResourceEx(resStream->Memory, resStream->Size, NULL, &FontsCount)) {

        ShowMessage("Can't load font to font table");
    }

    FreeLibrary(Resource);
}


void TFrMain::setLogo() {

    LLogo->Font->Name = "Sixtyfour";
    LLogo->Font->Size = 28;
    LLogo->Font->Color = TColor(0xEBCE87);
    LLogo->Caption = "KeyType";

}
//---------------------------------------------------------------------------

