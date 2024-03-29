#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <SysUtils.hpp>
#include <memory>

#include "Generator.h"
#include "UnitTestLogger.h"

class TTestGenerator : public TTestCase
{
	public:
		__fastcall virtual TTestGenerator(System::String name) : TTestCase(name) {}
		virtual void __fastcall SetUp();
		virtual void __fastcall TearDown();

	__published:
		void __fastcall TestgenerateText();
		void __fastcall TestgenerateWord();
		void __fastcall TestshuffleChars();

	private:
		int testCount;

		int maxChars;

		UnicodeString letters;
		bool uppercase;
		bool numbers;
		bool punctuation;

		UnicodeString inputText;

};


void __fastcall TTestGenerator::SetUp()
{
	testCount = 10;

	maxChars = 50;

	letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	uppercase = true;
	numbers = false;
	punctuation = false;

	inputText = "Sunny Hvar";

	LOGGER_LOG("Starting test...");

}

void __fastcall TTestGenerator::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}

void __fastcall TTestGenerator::TestgenerateText()
{

	for (int i = 0; i < testCount; i++) {

		UnicodeString result = Generator::generateText(letters, GeneratorOptions(uppercase, numbers, punctuation, 5, 10));

		LOGGER_LOG("Test " + IntToStr(i + 1) + ": " + result);

	}

}
    
void __fastcall TTestGenerator::TestgenerateWord()
{

	for (int i = 0; i < testCount; i++) {

		UnicodeString result = Generator::generateWord(letters, GeneratorOptions(uppercase, numbers, punctuation, 5, 10));

		LOGGER_LOG("Test " + IntToStr(i + 1) + ": " + result);

		if (!uppercase && !numbers && !punctuation) {

			for (int i = 1; i <= result.Length(); i++)
			{
				if (letters.Pos(result[i]) == 0)
				{
					LOGGER_LOG("Invalid char: " + UnicodeString(result[i]));
					return;
				}
			}
		}

	}

}

void __fastcall TTestGenerator::TestshuffleChars()
{

	for (int i = 0; i < testCount; i++) {

        UnicodeString result = Generator::shuffleChars(inputText);
        LOGGER_LOG("Test " + IntToStr(i + 1) + ": " + result);
        CheckNotEquals(inputText, result, L"Words are the same");
	}

}

static void registerTests()
{
  Testframework::RegisterTest(TTestGenerator::Suite());
}
#pragma startup registerTests 33
