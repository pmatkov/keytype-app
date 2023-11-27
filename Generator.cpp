//---------------------------------------------------------------------------


#include<cstdlib>
#include "Generator.h"
#include <cwctype>

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

bool Generator::seedInitialized = false;

void Generator::InitializeRandomSeed() {

        if (!seedInitialized) {
            srand(static_cast<unsigned>(time(nullptr)));
            seedInitialized = true;
        }
	}

UnicodeString Generator::generateText(UnicodeString letters, bool useUppercase, bool useNumbers, bool usePunctuation, int maxChars) {

		int charCount = 0;
		UnicodeString text;

		while (charCount < maxChars) {

			UnicodeString word = generateWord(letters, useUppercase, useNumbers, usePunctuation) + ' ';

			charCount += word.Length();
			text += word;
		}

		text.Delete(text.Length(), 1);

		return text;

}

UnicodeString Generator::generateWord(UnicodeString letters, bool useUppercase, bool useNumbers, bool usePunctuation) {

		UnicodeString numbers = "0123456789";
		UnicodeString punctuation = "!?/\\\"#$%&*=+',.:;-<>@^_()[]{}|";
		UnicodeString characters = "";

		const int MIN_CHARS = 1;
		const int MAX_CHARS = 12;

		if (letters.Length() || useNumbers || usePunctuation) {

			UnicodeString word;
			int wordLength = getRandomInt(MIN_CHARS, MAX_CHARS);

			for (int i = 0; i < wordLength; i++) {

				if (letters.Length()) {
					characters += letters;
				}
				if (useNumbers) {
					numbers = shuffleChars(numbers);
					characters += numbers.SubString(1, letters.Length() || usePunctuation ? 0.3 * numbers.Length() : numbers.Length());
				}
				if (usePunctuation) {
					numbers = shuffleChars(characters);
					characters += punctuation.SubString(1, letters.Length() || useNumbers ? 0.2 * punctuation.Length() : punctuation.Length());
				}

				characters = shuffleChars(characters);
				int index = getRandomInt(1, characters.Length());

				if (useUppercase && getRandomInt(0, 10) < 1) {
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


int Generator::getRandomInt(int minRange, int maxRange) {

	InitializeRandomSeed();

	return rand() % (maxRange + 1 - minRange) + minRange;
}

UnicodeString Generator::shuffleChars(UnicodeString input) {

	int len = input.Length();

	for (int i = 1; i < len; i++) {

		int j = i + getRandomInt(0, len - i);

		std::swap(input[i], input[j]);
	}

	return input;
}
