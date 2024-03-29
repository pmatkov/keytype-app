//---------------------------------------------------------------------------
#include "Generator.h"
#include "Random.h"
#include <cwctype>

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)


GeneratorOptions::GeneratorOptions(bool _useNumbers, bool _useUppercase,  bool _usePunctuation, int _min, int _max) : useNumbers(_useNumbers), useUppercase(_useUppercase), \
usePunctuation(_usePunctuation), min(_min), max(_max) {}

bool GeneratorOptions::getUseNumbers() const {
     return useNumbers;
}
bool GeneratorOptions::getUseUppercase() const {
    return useUppercase;
}
bool GeneratorOptions::getUsePunctuation() const {
     return usePunctuation;
}
int GeneratorOptions::getMin() const {
     return min;
}
int GeneratorOptions::getMax() const  {
     return max;
}


namespace Generator {


    UnicodeString generateChars(UnicodeString letters, int maxChars) {

        UnicodeString text = "";

        for (int i = 0; i < maxChars; i++) {
            text += letters[Random::getRandom(1, letters.Length())];
        }
  	    return text;
    }

    UnicodeString generateText(UnicodeString letters, GeneratorOptions options) {

        int maxWords = Random::getRandom(options.getMin(), options.getMax());
        UnicodeString text = "";

         for (int i = 0; i < maxWords; i++) {
            text += generateWord(letters, options);
            if (i < maxWords - 1) {
               text += " ";
            }
        }

        return text;
    }

    UnicodeString generateWord(UnicodeString letters, GeneratorOptions options) {

        UnicodeString numbers = "0123456789";
        UnicodeString punctuation = "!?/\\\"#$%&*=+',.:;-<>@^_()[]{}|";
        UnicodeString characters = "";

        if (letters.Length() || options.getUseNumbers() || options.getUsePunctuation()) {

            UnicodeString word;
            int wordLength = Random::getRandom(3, 12);

            for (int i = 0; i < wordLength; i++) {

                if (letters.Length()) {
                    characters += letters;
                }
                if (options.getUseNumbers()) {
                    numbers = shuffleChars(numbers);
                    characters += numbers.SubString(1, letters.Length() || options.getUsePunctuation() ? 0.3 * numbers.Length() : numbers.Length());
                }
                if (options.getUsePunctuation()) {
                    numbers = shuffleChars(characters);
                    characters += punctuation.SubString(1, letters.Length() || options.getUseNumbers() ? 0.2 * punctuation.Length() : punctuation.Length());
                }

                characters = shuffleChars(characters);
                int index = Random::getRandom(1, characters.Length());

                if (options.getUseUppercase() && Random::getRandom(0, 10) < 1) {
                    word += characters[index];
                }
                else {
                    word += towlower(characters[index]);
                }
            }

            return word;
        }

        else
            return L"";
    }

    UnicodeString shuffleChars(UnicodeString input) {

        int len = input.Length();

        for (int i = 1; i < len; i++) {

            int j = i + Random::getRandom(0, len - i);

            std::swap(input[i], input[j]);
        }

        return input;
    }
}


