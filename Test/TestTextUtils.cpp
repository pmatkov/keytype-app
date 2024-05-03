#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <SysUtils.hpp>
#include <vector>
#include <memory>


#include "TextUtils.h"
#include "UnitTestLogger.h"

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
		void __fastcall TestsplitToTokens();
        void __fastcall TestreplaceChar();
        void __fastcall TestisWordBreak();
        void __fastcall TestcountCharsUntilWordBreak();
		void __fastcall TestformatJson();
		void __fastcall TestrepeatChar();

};


void __fastcall TTestTextUtils::SetUp() {

	LOGGER_LOG("Starting test...");

	}

void __fastcall TTestTextUtils::TearDown() {

   	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}

void __fastcall TTestTextUtils::TestcountSentences()
{
	int testValue = TextUtils::countSentences("Coding in C++ is  challenging! My favorite song is \"Smells Like Teen Spirit\" by Nirvana. \
	The password must contain at least 8 characters, including !, #, or @.");
	CheckEquals(3, testValue);
}
    
void __fastcall TTestTextUtils::TestcountWords()
{
	CheckEquals(9, TextUtils::countWords("The password must contain at least 8 characters, including !, #, or @."));
}

void __fastcall TTestTextUtils::TestcountChars()
{
	CheckEquals(10, TextUtils::countChars("Hello, 123!"));
	CheckEquals(14, TextUtils::countChars("   Example	string."));
}

void __fastcall TTestTextUtils::TestisEndChar()
{

	CheckTrue(TextUtils::isEndChar(L'!'));
	CheckFalse(TextUtils::isEndChar(L'-'));
}
    
void __fastcall TTestTextUtils::TesttrimCharacters()
{
//
//    LOGGER_LOG("Expected: Ferrari Result: " + TextUtils::trimCharacters("\"Ferrari\"", L'\"'));
//	CheckEquals(UnicodeString("Ferrari"), TextUtils::trimCharacters("\"Ferrari\"", L'\"'));

        LOGGER_LOG("Expected: Result: " + TextUtils::trimCharacters("\"\"", L'\"'));
	CheckEquals(UnicodeString(""), TextUtils::trimCharacters("\"\"", L'\"'));

	LOGGER_LOG("Expected: Fast & Furious Result: " + TextUtils::trimCharacters("   Fast & Furious  ", L' '));
	CheckEquals(UnicodeString("Fast & Furious"), TextUtils::trimCharacters("   Fast & Furious  ", L' '));
}

void __fastcall TTestTextUtils::TestsplitToTokens() {

   std::vector<UnicodeString> testValue = TextUtils::splitToTokens("Back to the future");
   UnicodeString expectedValue[] = {"Back", "to", "the", "future"};

   for (int i = 0; i < testValue.size();  i++) {

   	LOGGER_LOG(IntToStr((int)i+1) + "/ Expected: " + expectedValue[i] + " Result:" + testValue[i]);
    CheckEquals(testValue[i], expectedValue[i]);
   }
}

void __fastcall TTestTextUtils::TestisWordBreak() {

 	UnicodeString testString = "Back to the future";
    int i;

    LOGGER_LOG("Test string: " + testString);

    for (i = 1; i <= testString.Length(); i++) {

    	LOGGER_LOG("Index: " + IntToStr(i) + " substring:" + testString.SubString(1, i));

        if (!TextUtils::isWordBreak(testString, i)) {
           break;
        }
    }

    CheckEquals(i, 4);
}

void __fastcall TTestTextUtils::TestreplaceChar() {

 	UnicodeString testString = "Back to the future";

    LOGGER_LOG("Test string: " + testString);
    UnicodeString result = TextUtils::replaceChar(testString, ' ', L'\u00B7');

    LOGGER_LOG("Result: " + result);
    CheckEquals(result, L"Back\u00B7to\u00B7the\u00B7future");
}

void __fastcall TTestTextUtils::TestcountCharsUntilWordBreak() {

 	UnicodeString testString = "Back to the future";
    UnicodeString breakString = "Back to the";

	int result = TextUtils::countCharsUntilWordBreak(testString, testString.Length()-1);

    LOGGER_LOG("Result: " + IntToStr(result) + " " + breakString.Length());
    CheckEquals(result, breakString.Length());
}


void __fastcall TTestTextUtils::TestformatJson() {

	UnicodeString input = "{\"animals\":[{\"title\":\"Penguin\",\"origin\":\"Madagascar\",\"age\":\"4\"},{\"title\":\"Penguin\",\"origin\":\"Antarctica\",\"age\":\"5\"}]}";
	UnicodeString result = TextUtils::formatJson(input);
	LOGGER_LOG("Input:" + input);
	LOGGER_LOG("Result:" + result);
}


void __fastcall TTestTextUtils::TestrepeatChar() {

	 UnicodeString result = TextUtils::generateStringFromChar('x', 4);
	 CheckEquals(result, "xxxx");
}


static void registerTests()
{
  Testframework::RegisterTest(TTestTextUtils::Suite());
}
#pragma startup registerTests 33
