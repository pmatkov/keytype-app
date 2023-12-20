//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CustomTextFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrCustomText *FrCustomText;
//---------------------------------------------------------------------------
__fastcall TFrCustomText::TFrCustomText(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
