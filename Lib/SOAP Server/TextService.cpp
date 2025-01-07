// ************************************************************************ //
// Implementation class for interface ITextWebService
// ************************************************************************ //
#include <stdio.h>
#include <vcl.h>
#include <cwctype>
#pragma hdrstop

#if !defined(__TextWebService_h__)
#include "TextService.h"
#include "Random.h"
#endif

// ************************************************************************ //
//  TTextWebServiceImpl implements interface ITextWebService
// ************************************************************************ //
class TTextWebServiceImpl : public TInvokableClass, public ITextWebService
{
public:
	UnicodeString generateText(const TStringArray wordList, int minChars, int maxChars, int minWords, int maxWords, bool useUppercase);
    UnicodeString shuffleWords(UnicodeString words);

  /* IUnknown */
  HRESULT STDMETHODCALLTYPE QueryInterface(const GUID& IID, void **Obj)
                        { return GetInterface(IID, Obj) ? S_OK : E_NOINTERFACE; }
  ULONG STDMETHODCALLTYPE AddRef() { return TInvokableClass::_AddRef();  }
  ULONG STDMETHODCALLTYPE Release() { return TInvokableClass::_Release();  }
};


UnicodeString TTextWebServiceImpl::generateText(const TStringArray wordList, int minChars, int maxChars, int minWords, int maxWords, bool useUppercase)
{
   	TStringArray filteredWordList;
    UnicodeString generatedText = "";

    if ((!maxChars && minChars > maxChars) || minWords > maxWords) {
       return generatedText;
    }

    filteredWordList.Length = 0;

   for (int i = 0, j = 0; i < wordList.Length; i++) {
        UnicodeString word = wordList[i];

        if ((!maxChars && word.Length() >= minChars) || (word.Length() >= minChars && word.Length() <= maxChars)) {

          	filteredWordList.Length = filteredWordList.Length + 1;
        	filteredWordList[j++] = word;
        }
    }

    int wordCount = minWords < maxWords ? Random::getRandom(minWords, maxWords) : minWords;
    int maxUppercase = wordCount;

    while (wordCount--) {


        int index = Random::getRandom(0, filteredWordList.Length - 1);

        UnicodeString word = filteredWordList[index];

        if (useUppercase && Random::getRandom(0, 1) && (maxUppercase--)) {
           word[Random::getRandom(1, word.Length())] = towupper(word[Random::getRandom(1, word.Length())]);
        }

        generatedText += word;

        if (wordCount > 0) {
            generatedText += " ";
        }
    }

    return generatedText;

}

UnicodeString TTextWebServiceImpl::shuffleWords(UnicodeString words)
{
    TStringDynArray wordArray = SplitString(words, " ");
    int wordCount = wordArray.Length;

    for (int i = 0; i < wordCount - 1; i++) {

        int j = Random::getRandom(i, wordCount - 1);
        std::swap(wordArray[i], wordArray[j]);
    }

    UnicodeString shuffledText = "";

    for (int i = 0; i < wordCount; i++) {

        shuffledText += wordArray[i];

        if (i < wordCount - 1) {
            shuffledText += " ";
        }
    }

    return shuffledText;
}



static void __fastcall TextWebServiceFactory(System::TObject* &obj)
{
  static _di_ITextWebService iInstance;
  static TTextWebServiceImpl *instance = 0;
  if (!instance)
  {
    instance = new TTextWebServiceImpl();
    instance->GetInterface(iInstance);
  }
  obj = instance;
}

// ************************************************************************ //
//  The following routine registers the interface and implementation class
//  as well as the type used by the methods of the interface
// ************************************************************************ //
static void RegTypes()
{
  InvRegistry()->RegisterInterface(__delphirtti(ITextWebService));
  InvRegistry()->RegisterInvokableClass(__classid(TTextWebServiceImpl), TextWebServiceFactory);
}
#pragma startup RegTypes 32

