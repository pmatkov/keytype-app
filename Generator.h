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
		static UnicodeString generateText(UnicodeString letters, bool useUppercase, bool useNumbers, bool usePunctuation, int maxChars);
		static UnicodeString generateWord(UnicodeString letters, bool useUppercase, bool useNumbers, bool usePunctuation);
		static int getRandomInt(int minRange, int maxRange);
		static UnicodeString shuffleChars(UnicodeString input);

};

#endif
