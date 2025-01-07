
//---------------------------------------------------------------------------
#include "WebModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TComponentClass WebModuleClass = __classid(TWebModule1);
//---------------------------------------------------------------------------
__fastcall TWebModule1::TWebModule1(TComponent* Owner)
	: TWebModule(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModule1DefaultHandlerAction(TObject *Sender,
      TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
  WSDLHTMLPublish1->ServiceInfo(Sender, Request, Response, Handled);
}
//---------------------------------------------------------------------------


