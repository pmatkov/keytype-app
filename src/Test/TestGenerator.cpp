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
		void __fastcall TestgenerateTokenSequence();
		void __fastcall TestgenerateToken();
		void __fastcall TestshuffleChars();

	private:
        Generator generator;

        UnicodeString letters = L"abcdefghijklmnopqrstuvwxyz";
        bool useNumbers = false;
        bool useUppercase = false;
        bool usePunctuation = false;

		int testCount = 10;
		int minChars = 5;
        int maxChars = 10;

		UnicodeString input = L"Sunny Hvar";

};


void __fastcall TTestGenerator::SetUp()
{
	generator = Generator(letters, useNumbers, useUppercase, usePunctuation);
	LOGGER_LOG("Starting test...");

}

void __fastcall TTestGenerator::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}

void __fastcall TTestGenerator::TestgenerateTokenSequence()
{

	for (int i = 0; i < testCount; i++) {

		UnicodeString result = generator.generateTokenSequence(minChars, maxChars, 10, 10);

		LOGGER_LOG("Test " + IntToStr(i + 1) + ": " + result);
	}
}
    
void __fastcall TTestGenerator::TestgenerateToken()
{

	for (int i = 0; i < testCount; i++) {

		UnicodeString result = generator.generateToken(minChars, maxChars);

		LOGGER_LOG("Test " + IntToStr(i + 1) + ": " + result);

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

void __fastcall TTestGenerator::TestshuffleChars()
{

	for (int i = 0; i < testCount; i++) {

        UnicodeString result = generator.shuffleChars(input);
        LOGGER_LOG("Test " + IntToStr(i + 1) + ": " + result);
        CheckNotEquals(input, result, L"Words are the same");
	}

}

static void registerTests()
{
  Testframework::RegisterTest(TTestGenerator::Suite());
}
#pragma startup registerTests 33
