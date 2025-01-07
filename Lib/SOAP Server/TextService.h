// ************************************************************************ //
// Invokable interface declaration header for TextWebService
// ************************************************************************ //
#ifndef   TextServiceH
#define   TextServiceH

#include <vector>

#include <System.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.XSBuiltIns.hpp>
#include <System.Types.hpp>
#include <System.StrUtils.hpp>


typedef DynamicArray<AnsiString>  TStringArray;


// ************************************************************************ //
//  Invokable interfaces must derive from IInvokable
//  The methods of the interface will be exposed via SOAP
// ************************************************************************ //
__interface INTERFACE_UUID("{8BF35A91-E315-4935-85EF-A795BEB2C8E6}") ITextWebService : public IInvokable
{
public:

    virtual UnicodeString generateText(const TStringArray wordList, int minChars, int maxChars, int minWords, int maxWords, bool useUppercase) = 0;
    virtual UnicodeString shuffleWords(UnicodeString words) = 0;

};
typedef DelphiInterface<ITextWebService> _di_ITextWebService;


#endif // TextWebServiceH
//---------------------------------------------------------------------------


