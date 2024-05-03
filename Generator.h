//---------------------------------------------------------------------------

#ifndef GeneratorH
#define GeneratorH
//---------------------------------------------------------------------------
#include <vcl.h>

class GeneratorOptions {

    private:
        bool useNumbers;
        bool useUppercase;
        bool usePunctuation;
        int min;
        int max;

    public:
        GeneratorOptions(bool _useNumbers = false, bool _useUppercase = false,  bool _usePunctuation = false, int _min = 0, int _max = 0);
        bool getUseNumbers() const;
        bool getUseUppercase() const;
        bool getUsePunctuation() const;
        int getMin() const;
        int getMax() const;
};

namespace Generator {

    UnicodeString generateChars(UnicodeString letters, int maxChars);
    UnicodeString generateText(UnicodeString letters, GeneratorOptions options);
    UnicodeString generateWord(UnicodeString letters, GeneratorOptions options);
    UnicodeString shuffleChars(UnicodeString input);

};

#endif
