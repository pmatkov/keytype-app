#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <SysUtils.hpp>
#include "Generator.h"
#include "Logger.h"

class TTestGenerator : public TTestCase
{
	public:
		__fastcall virtual TTestGenerator(System::String name) : TTestCase(name) {}
		virtual void __fastcall SetUp();
		virtual void __fastcall TearDown();

	__published:
		void __fastcall TestgenerateText();
		void __fastcall TestgenerateWord();
		void __fastcall TestgetRandomInt();
		void __fastcall TestshuffleChars();

	private:
		Logger* logger;
		int testCount;

		int maxChars;

		UnicodeString letters;
		bool uppercase;
		bool numbers;
		bool punctuation;

		int minInt;
		int maxInt;

		UnicodeString inputText;

};


void __fastcall TTestGenerator::SetUp()
{
	logger = new Logger;
	testCount = 10;

	maxChars = 50;

	letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	uppercase = true;
	numbers = false;
	punctuation = false;

	minInt = 0;
	maxInt = 10;
	inputText = "Sunny Hvar";

	logger->log("Starting test...");

}

void __fastcall TTestGenerator::TearDown()
{
	logger->log("Test completed.");

	if (logger)
	{
		if(logger->getLogStringList()->Count > 0)
			ShowMessage(logger->getLogStringList()->Text);

	  	delete logger;
	}
}

void __fastcall TTestGenerator::TestgenerateText()
{


	for (int i = 0; i < testCount; i++) {

		UnicodeString result = Generator::generateText(letters, uppercase, numbers, punctuation, maxChars);

		logger->log("Test " + IntToStr(i + 1) + ": " + result);

	}


}
    
void __fastcall TTestGenerator::TestgenerateWord()
{

	for (int i = 0; i < testCount; i++) {

		UnicodeString result = Generator::generateWord(letters, uppercase, numbers, punctuation);

		logger->log("Test " + IntToStr(i + 1) + ": " + result);

		if (!uppercase && !numbers && !punctuation) {

			for (int i = 1; i <= result.Length(); i++)
			{
				if (letters.Pos(result[i]) == 0)
				{
					logger->log("Invalid char: " + result[i]);
					return;
				}
			}
		}

	}

}

void __fastcall TTestGenerator::TestgetRandomInt()
{


	for (int i = 0; i < testCount; i++) {

			int result = Generator::getRandomInt(minInt, maxInt);
			logger->log("Test " + IntToStr(i + 1) + ": " + IntToStr(result));
			CheckTrue(result >= minInt && result <= maxInt, L"Outside of range");
	}

}

void __fastcall TTestGenerator::TestshuffleChars()
{


	for (int i = 0; i < testCount; i++) {

			UnicodeString result = Generator::shuffleChars(inputText);
			logger->log("Test " + IntToStr(i + 1) + ": " + result);
			CheckTrue(inputText.Compare(result) != 0, L"Words are the same");
	}

}

static void registerTests()
{
  Testframework::RegisterTest(TTestGenerator::Suite());
}
#pragma startup registerTests 33
