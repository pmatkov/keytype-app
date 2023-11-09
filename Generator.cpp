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
            srand(static_cast<unsigned>(time(NULL)));
            seedInitialized = true;
        }
	}

UnicodeString Generator::generateText(UnicodeString letters, bool uppercase, bool numbers, bool punctuation, int maxChars) {

		int charCount = 0;
		UnicodeString text;

		while (charCount < maxChars) {

			UnicodeString word = generateWord(letters, uppercase, numbers, punctuation) + ' ';

			charCount += word.Length();
			text += word;
		}

		text.Delete(text.Length(), 1);

		return text;

}

UnicodeString Generator::generateWord(UnicodeString letters, bool uppercase, bool numbers, bool punctuation) {

		UnicodeString numChars = "0123456789";
		UnicodeString punctChars = "!?/\\\"#$%&*=+',.:;-<>@^_()[]{}|";

		const int MIN_CHARS = 1;
		const int MAX_CHARS = 12;
		const float MODIFIERS_RATIO = 0.2;

		if (letters.Length() > 0 || numbers || punctuation) {

			UnicodeString word;
			int wordLength = getRandomInt(MIN_CHARS, MAX_CHARS);
			int maxModififers = wordLength * MODIFIERS_RATIO;

			for (int i = 0, modifier = 0; i < wordLength; i++) {

				int index;

				if ((numbers || punctuation) && modifier < maxModififers && getRandomInt(0, 1)) {

					int modifierType = getRandomInt(0, 2);

					if (numbers && modifierType == 1) {
						index = getRandomInt(1, numChars.Length());
						word += numChars[index];
					}
					else if (punctuation && modifierType == 2) {
						index = getRandomInt(1, punctChars.Length());
						word += punctChars[index];
					}
					modifier++;
				}
				else {
					index = getRandomInt(1, letters.Length());
					if (uppercase && getRandomInt(0, 10) < 1) {
						 word += letters[index];
					}
					else {
						word += towlower(letters[index]);
					}
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
