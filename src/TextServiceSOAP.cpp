// ************************************************************************ //
// The types declared in this file were generated from data read from the
// WSDL File described below:
// WSDL     : C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Lib\SOAP Server\TextService.xml
//  >Import : C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Lib\SOAP Server\TextService.xml>0
// Version  : 1.0
// (28.6.2024. 22:55:11 - - $Rev: 112483 $)
// ************************************************************************ //

#include <System.hpp>
#pragma hdrstop

#include "TextServiceSOAP.h"



namespace NS_TextService {

_di_ITextWebService GetITextWebService(bool useWSDL, System::String addr, Soaphttpclient::THTTPRIO* HTTPRIO)
{
  static const char* defWSDL= "C:\\Users\\surf3r\\OneDrive\\Documents\\Embarcadero\\Studio\\Projects\\KeyType\\Lib\\SOAP Server\\TextService.xml";
  static const char* defURL = "http://localhost/SOAPServer.dll/soap/ITextWebService";
  static const char* defSvc = "ITextWebServiceservice";
  static const char* defPrt = "ITextWebServicePort";
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
  _di_ITextWebService service;
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
  /* ITextWebService */
  InvRegistry()->RegisterInterface(__delphirtti(ITextWebService), L"urn:TextService-ITextWebService", L"");
  InvRegistry()->RegisterDefaultSOAPAction(__delphirtti(ITextWebService), L"urn:TextService-ITextWebService#%operationName%");
  /* ITextWebService->generateText */
  InvRegistry()->RegisterParamInfo(__delphirtti(ITextWebService), "generateText", "return_", L"return", L"");
  /* ITextWebService->shuffleWords */
  InvRegistry()->RegisterParamInfo(__delphirtti(ITextWebService), "shuffleWords", "return_", L"return", L"");
  /* DynamicArray */
  RemClassRegistry()->RegisterXSInfo(__delphirtti(DynamicArray), L"urn:TextService", L"DynamicArray");
}
#pragma startup RegTypes 32

};     // NS_TextService

