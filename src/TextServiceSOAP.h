// ************************************************************************ //
// The types declared in this file were generated from data read from the
// WSDL File described below:
// WSDL     : C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Lib\SOAP Server\TextService.xml
//  >Import : C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\KeyType\Lib\SOAP Server\TextService.xml>0
// Version  : 1.0
// (28.6.2024. 22:55:11 - - $Rev: 112483 $)
// ************************************************************************ //

#ifndef   TextServiceSOAPH
#define   TextServiceSOAPH

#include <System.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.XSBuiltIns.hpp>
#include <Soap.SOAPHTTPClient.hpp>

#if !defined(SOAP_REMOTABLE_CLASS)
#define SOAP_REMOTABLE_CLASS __declspec(delphiclass)
#endif

namespace NS_TextService {

// ************************************************************************ //
// The following types, referred to in the WSDL document are not being represented
// in this file. They are either aliases[@] of other types represented or were referred
// to but never[!] declared in the document. The types from the latter category
// typically map to predefined/known XML or Embarcadero types; however, they could also 
// indicate incorrect WSDL documents that failed to declare or import a schema type.
// ************************************************************************ //
// !:boolean         - "http://www.w3.org/2001/XMLSchema"[]
// !:int             - "http://www.w3.org/2001/XMLSchema"[]
// !:string          - "http://www.w3.org/2001/XMLSchema"[Gbl]

typedef DynamicArray<UnicodeString> DynamicArray;   /* "urn:TextService"[GblCplx] */

// ************************************************************************ //
// Namespace : urn:TextService-ITextWebService
// soapAction: urn:TextService-ITextWebService#%operationName%
// transport : http://schemas.xmlsoap.org/soap/http
// style     : rpc
// use       : encoded
// binding   : ITextWebServicebinding
// service   : ITextWebServiceservice
// port      : ITextWebServicePort
// URL       : http://localhost/SOAPServer.dll/soap/ITextWebService
// ************************************************************************ //
__interface INTERFACE_UUID("{1EEE1FAF-4A24-0F26-2B75-C314B343FC31}") ITextWebService : public IInvokable
{
public:
  virtual UnicodeString   generateText(const DynamicArray wordList, const int minChars, const int maxChars, const int minWords, const int maxWords, const bool useUppercase) = 0; 
  virtual UnicodeString   shuffleWords(const UnicodeString words) = 0; 
};
typedef DelphiInterface<ITextWebService> _di_ITextWebService;

_di_ITextWebService GetITextWebService(bool useWSDL=false, System::String addr= System::String(), Soaphttpclient::THTTPRIO* HTTPRIO=0);


};     // NS_TextService

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace NS_TextService;
#endif



#endif // TextServiceH
