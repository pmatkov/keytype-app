// ************************************************************************ //
// The types declared in this file were generated from data read from the
// WSDL File described below:
// WSDL     : https://www.dataaccess.com/webservicesserver/TextCasing.wso?WSDL
//  >Import : https://www.dataaccess.com/webservicesserver/TextCasing.wso?WSDL>0
// Encoding : UTF-8
// Version  : 1.0
// (19.5.2024. 21:33:29 - - $Rev: 112483 $)
// ************************************************************************ //

#ifndef   TextCasingSOAPH
#define   TextCasingSOAPH

#include <System.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.XSBuiltIns.hpp>
#include <Soap.SOAPHTTPClient.hpp>

#if !defined(SOAP_REMOTABLE_CLASS)
#define SOAP_REMOTABLE_CLASS __declspec(delphiclass)
#endif
#if !defined(IS_REF)
#define IS_REF 0x0080
#endif


namespace NS_TextCasing {

// ************************************************************************ //
// The following types, referred to in the WSDL document are not being represented
// in this file. They are either aliases[@] of other types represented or were referred
// to but never[!] declared in the document. The types from the latter category
// typically map to predefined/known XML or Embarcadero types; however, they could also 
// indicate incorrect WSDL documents that failed to declare or import a schema type.
// ************************************************************************ //
// !:string          - "http://www.w3.org/2001/XMLSchema"[Gbl]



// ************************************************************************ //
// Namespace : http://www.dataaccess.com/webservicesserver/
// transport : http://schemas.xmlsoap.org/soap/http
// style     : document
// use       : literal
// binding   : TextCasingSoapBinding
// service   : TextCasing
// port      : TextCasingSoap
// URL       : https://www.dataaccess.com/webservicesserver/TextCasing.wso
// ************************************************************************ //
__interface INTERFACE_UUID("{B3FB46A5-456C-85C2-E5C0-11D23E75C436}") TextCasingSoapType : public IInvokable
{
public:
  virtual UnicodeString   TitleCaseWordsWithToken(const UnicodeString sText, const UnicodeString sToken) = 0; 
  virtual UnicodeString   InvertStringCase(const UnicodeString sAString) = 0; 
  virtual UnicodeString   InvertCaseFirstAdjustStringToPrevious(const UnicodeString sAString) = 0; 
  virtual UnicodeString   InvertCaseFirstAdjustStringToCurrent(const UnicodeString sAString) = 0; 
  virtual UnicodeString   AllUppercaseWithToken(const UnicodeString sAString, const UnicodeString sToken) = 0; 
  virtual UnicodeString   AllLowercaseWithToken(const UnicodeString sAString, const UnicodeString sToken) = 0; 
  virtual UnicodeString   UppercaseWordsWithToken(const UnicodeString sAString, const UnicodeString sToken) = 0; 
  virtual UnicodeString   LowercaseWordsWithToken(const UnicodeString sAString, const UnicodeString sToken) = 0;
};
typedef DelphiInterface<TextCasingSoapType> _di_TextCasingSoapType;

_di_TextCasingSoapType GetTextCasingSoapType(bool useWSDL=false, System::String addr= System::String(), Soaphttpclient::THTTPRIO* HTTPRIO=0);


};     // NS_TextCasing

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace NS_TextCasing;
#endif



#endif // TextCasingH
