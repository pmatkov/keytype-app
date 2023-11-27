#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <SysUtils.hpp>
#include <vector>
#include "TextUtils.h"
#include "Logger.h"

class TTestTextUtils : public TTestCase
{
	public:
		__fastcall virtual TTestTextUtils(System::String name) : TTestCase(name) {}
		virtual void __fastcall SetUp();
		virtual void __fastcall TearDown();
  
	__published:
		void __fastcall TestcountSentences();
		void __fastcall TestcountWords();
		void __fastcall TestcountChars();
		void __fastcall TestisEndChar();
		void __fastcall TesttrimCharacters();
		void __fastcall TestsplitTextIntoWords();
		void __fastcall TestformatJson();
		void __fastcall TestrepeatChar();

	private:
				Logger* logger;
};


void __fastcall TTestTextUtils::SetUp() {

	logger = new Logger;

	logger->log("Starting test...");

	}

void __fastcall TTestTextUtils::TearDown() {

   	logger->log("Test completed.");

	if (logger)
	{
		if(logger->getLogStringList()->Count > 0)
			ShowMessage(logger->getLogStringList()->Text);

	  	delete logger;
	}
}

void __fastcall TTestTextUtils::TestcountSentences()
{

	int result = TextUtils::countSentences("Coding in C++ is  challenging! My favorite song is \"Smells Like Teen Spirit\" by Nirvana. \
	The password must contain at least 8 characters, including !, #, or @.");
	CheckEquals(3, result);
}
    
void __fastcall TTestTextUtils::TestcountWords()
{

	int result = TextUtils::countWords("The password must contain at least 8 characters, including !, #, or @.");
	CheckEquals(9, result);
}

void __fastcall TTestTextUtils::TestcountChars()
{

	int result = TextUtils::countChars("Hello, 123!");
	CheckEquals(10, result);

	int result2 = TextUtils::countChars("   Example	string.");
	CheckEquals(14, result2);

}


void __fastcall TTestTextUtils::TestisEndChar()
{
	int result = TextUtils::isEndChar(L'!');
	CheckTrue(result);

	int result2 = TextUtils::isEndChar(L'-');
	CheckFalse(result2);
}
    
void __fastcall TTestTextUtils::TesttrimCharacters()
{

	UnicodeString result = TextUtils::trimCharacters("\"Ferrari\"", L'\"');
	CheckEquals(UnicodeString("Ferrari"), result);

	result = TextUtils::trimCharacters("   Fast & Furious  ", L' ');
	CheckEquals(UnicodeString("Fast & Furious"), result);
}

void __fastcall TTestTextUtils::TestsplitTextIntoWords() {
	 std::vector<UnicodeString> result = TextUtils::splitTextIntoWords("Back to the future");
	 UnicodeString reference[] = {"Back", "to", "the", "future"};

	 for (size_t i = 0; i < result.size();  i++) {

		CheckEquals(result[i], reference[i]);
	 }

}

void __fastcall TTestTextUtils::TestformatJson() {

	UnicodeString input = "{\"animals\":[{\"title\":\"Penguin\",\"origin\":\"Madagascar\",\"age\":\"4\"},{\"title\":\"Penguin\",\"origin\":\"Antarctica\",\"age\":\"5\"}]}";
	UnicodeString result = TextUtils::formatJson(input);
	logger->log("Input:" + input);
	logger->log("Result:" + result);
}


void __fastcall TTestTextUtils::TestrepeatChar() {

	 UnicodeString result = TextUtils::repeatChar('x', 4);
	 CheckEquals(result, "xxxx");
}


static void registerTests()
{
  Testframework::RegisterTest(TTestTextUtils::Suite());
}
#pragma startup registerTests 33
