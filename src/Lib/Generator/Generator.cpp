//---------------------------------------------------------------------------

#pragma hdrstop

#include "Generator.h"
#include "Random.h"
#include "TextService.h"

#include <cwctype>
//---------------------------------------------------------------------------
#pragma package(smart_init)


Generator::Generator() {}

Generator::Generator(UnicodeString _letters, bool _useNumbers, bool _useUppercase, bool _usePunctuation) : letters(_letters), useNumbers(_useNumbers), \
	useUppercase(_useUppercase), usePunctuation(_usePunctuation) {}
Generator::Generator(bool _useNumbers, bool _useUppercase, bool _usePunctuation) : useNumbers(_useNumbers), useUppercase(_useUppercase), usePunctuation(_usePunctuation) {}


UnicodeString Generator::generateChars(int charCount) {

    UnicodeString generatedChars = "";

    for (int i = 0; i < charCount; i++) {
        generatedChars += letters[Random::getRandom(1, letters.Length())];
    }
    return generatedChars;
}

UnicodeString Generator::generateToken(int minChars, int maxChars) {

    UnicodeString num = numbers;
    UnicodeString punct = punctuation;
    UnicodeString token = "";

    if (letters.Length() || useNumbers || usePunctuation) {

        int tokenLen = Random::getRandom(minChars, maxChars);
        UnicodeString modToken = "";

        for (int i = 0; i < tokenLen; i++) {

            if (letters.Length()) {
                token += letters;
            }
            if (useNumbers) {
                num = shuffleChars(num);
                token += num.SubString(1, letters.Length() || usePunctuation ? 0.3 * num.Length() : num.Length());
            }
            if (usePunctuation) {
                num = shuffleChars(token);
                token += punct.SubString(1, letters.Length() || useNumbers ? 0.2 * punct.Length() : punct.Length());
            }

            token = shuffleChars(token);
            int index = Random::getRandom(1, token.Length());

            if (useUppercase && Random::getRandom(0, 10) < 1) {
                modToken += towupper(token[index]);
            }
            else {
                modToken += token[index];
            }
        }

        return modToken;
    }

    return token;
}

UnicodeString Generator::generateTokenSequence(int minChars, int maxChars, int minTokens, int maxToxens) {

    int tokenCount = Random::getRandom(minTokens, maxToxens);
    UnicodeString generatedTokenSequence = "";

     for (int i = 0; i < tokenCount; i++) {

        generatedTokenSequence += generateToken(minChars, maxChars);

        if (i < tokenCount - 1) {
           generatedTokenSequence += " ";
        }
    }

    return generatedTokenSequence;
}

UnicodeString Generator::shuffleChars(UnicodeString string) {

    int stringLen = string.Length();

    for (int i = 1; i < stringLen; i++) {

        int j = i + Random::getRandom(0, stringLen - i);

        std::swap(string[i], string[j]);
    }

    return string;
}

UnicodeString Generator::shuffleWords(UnicodeString words) {

    _di_ITextWebService textService = GetITextWebService();

    UnicodeString result = textService->shuffleWords(words);

    return result;

}

UnicodeString Generator::generateText(const std::vector<UnicodeString> &wordList, int minChars, int maxChars, int minWords, int maxWords) {

	DynamicArray<UnicodeString> stringArray;

    stringArray.Length = wordList.size();

    for (int i = 0; i < wordList.size(); i++) {
        stringArray[i] = wordList[i];
    }

    _di_ITextWebService textService = GetITextWebService();

    UnicodeString result = textService->generateText(stringArray, minChars, maxChars, minWords, maxWords, useUppercase);

    return result;

}
