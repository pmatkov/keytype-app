//---------------------------------------------------------------------------

#ifndef GeneratorH
#define GeneratorH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>

class Generator {

    private:
        UnicodeString letters = L"abcdefghijklmnopqrstuvwxyz";
        UnicodeString numbers = "0123456789";
        UnicodeString punctuation = "!?/\\\"#$%&*=+',.:;-<>@^_()[]{}|";
        bool useNumbers = false;
        bool usePunctuation = false;
        bool useUppercase = false;

    public:
    	Generator();
        Generator(UnicodeString _letters, bool _useNumbers, bool _useUppercase, bool _usePunctuation);
        Generator(bool _useNumbers, bool _useUppercase, bool _usePunctuation);

        UnicodeString generateChars(int charCount);
    	UnicodeString generateToken(int minChars, int maxChars);
        UnicodeString generateTokenSequence(int minChars, int maxChars, int minTokens, int maxToxens);
        UnicodeString shuffleChars(UnicodeString string);

        UnicodeString shuffleWords(UnicodeString words);
        UnicodeString generateText(const std::vector<UnicodeString> &wordList, int minChars, int maxChars, int minWords, int maxWords);

};

#endif
