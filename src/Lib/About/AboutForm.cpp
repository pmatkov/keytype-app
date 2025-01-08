//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AboutForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAbout *FAbout;
//---------------------------------------------------------------------------
__fastcall TFAbout::TFAbout(TComponent* Owner) 	: TForm(Owner) {}

 void CreateAboutForm() {
    TFAbout *FAbout = new TFAbout(nullptr);
    FAbout->Position = poMainFormCenter;
    FAbout->ShowModal();
    delete FAbout;
 }
//---------------------------------------------------------------------------
