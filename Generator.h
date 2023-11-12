//---------------------------------------------------------------------------

#ifndef GeneratorH
#define GeneratorH
//---------------------------------------------------------------------------
#include <vcl.h>

class Generator {

	private:
		static bool seedInitialized;

	public:
		static void InitializeRandomSeed();
		static UnicodeString generateText(UnicodeString letters, bool uppercase, bool numbers, bool punctuation, int maxChars);
		static UnicodeString generateWord(UnicodeString letters, bool uppercase, bool numbers, bool punctuation);
		static int getRandomInt(int minRange, int maxRange);
		static UnicodeString shuffleChars(UnicodeString input);

};

#endif
