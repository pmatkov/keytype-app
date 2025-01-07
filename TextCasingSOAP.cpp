// ************************************************************************ //
// The types declared in this file were generated from data read from the
// WSDL File described below:
// WSDL     : https://www.dataaccess.com/webservicesserver/TextCasing.wso?WSDL
//  >Import : https://www.dataaccess.com/webservicesserver/TextCasing.wso?WSDL>0
// Encoding : UTF-8
// Version  : 1.0
// (19.5.2024. 21:33:29 - - $Rev: 112483 $)
// ************************************************************************ //

#include <System.hpp>
#pragma hdrstop

#include "TextCasingSOAP.h"



namespace NS_TextCasing {

_di_TextCasingSoapType GetTextCasingSoapType(bool useWSDL, System::String addr, Soaphttpclient::THTTPRIO* HTTPRIO)
{
  static const char* defWSDL= "https://www.dataaccess.com/webservicesserver/TextCasing.wso?WSDL";
  static const char* defURL = "https://www.dataaccess.com/webservicesserver/TextCasing.wso";
  static const char* defSvc = "TextCasing";
  static const char* defPrt = "TextCasingSoap";
  if (addr=="")
    addr = useWSDL ? defWSDL : defURL;
  Soaphttpclient::THTTPRIO* rio = HTTPRIO ? HTTPRIO : new Soaphttpclient::THTTPRIO(0);
  if (useWSDL) {
    rio->WSDLLocation = addr;
    rio->Service = defSvc;
    rio->Port = defPrt;
  } else {
    rio->URL = addr;
  }
  _di_TextCasingSoapType service;
  rio->QueryInterface(service);
  if (!service && !HTTPRIO)
    delete rio;
  return service;
}


// ************************************************************************ //
// This routine registers the interfaces and types exposed by the WebService.
// ************************************************************************ //
static void RegTypes()
{
  /* TextCasingSoapType */
  InvRegistry()->RegisterInterface(__delphirtti(TextCasingSoapType), L"http://www.dataaccess.com/webservicesserver/", L"UTF-8");
  InvRegistry()->RegisterDefaultSOAPAction(__delphirtti(TextCasingSoapType), L"");
  InvRegistry()->RegisterInvokeOptions(__delphirtti(TextCasingSoapType), ioDocument);
  /* TextCasingSoapType.TitleCaseWordsWithToken */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "TitleCaseWordsWithToken", "",
                                    "[ReturnName='TitleCaseWordsWithTokenResult']" );
  /* TextCasingSoapType.InvertStringCase */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "InvertStringCase", "",
                                    "[ReturnName='InvertStringCaseResult']" );
  /* TextCasingSoapType.InvertCaseFirstAdjustStringToPrevious */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "InvertCaseFirstAdjustStringToPrevious", "",
                                    "[ReturnName='InvertCaseFirstAdjustStringToPreviousResult']" );
  /* TextCasingSoapType.InvertCaseFirstAdjustStringToCurrent */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "InvertCaseFirstAdjustStringToCurrent", "",
                                    "[ReturnName='InvertCaseFirstAdjustStringToCurrentResult']" );
  /* TextCasingSoapType.AllUppercaseWithToken */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "AllUppercaseWithToken", "",
                                    "[ReturnName='AllUppercaseWithTokenResult']" );
  /* TextCasingSoapType.AllLowercaseWithToken */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "AllLowercaseWithToken", "",
                                    "[ReturnName='AllLowercaseWithTokenResult']" );
  /* TextCasingSoapType.UppercaseWordsWithToken */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "UppercaseWordsWithToken", "",
                                    "[ReturnName='UppercaseWordsWithTokenResult']" );
  /* TextCasingSoapType.LowercaseWordsWithToken */
  InvRegistry()->RegisterMethodInfo(__delphirtti(TextCasingSoapType), "LowercaseWordsWithToken", "",
                                    "[ReturnName='LowercaseWordsWithTokenResult']" );
}
#pragma startup RegTypes 32

};     // NS_TextCasing

