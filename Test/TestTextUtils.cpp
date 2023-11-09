#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <SysUtils.hpp>
#include "TextUtils.h"

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
		void __fastcall TesttrimSpaces();
};


void __fastcall TTestTextUtils::SetUp() {}

void __fastcall TTestTextUtils::TearDown() {}

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
    
void __fastcall TTestTextUtils::TesttrimSpaces()
{
	UnicodeString result = TextUtils::trimSpaces("   Fast  &   Furious  ");
	CheckEquals(UnicodeString("Fast & Furious"), result);
}


static void registerTests()
{
  Testframework::RegisterTest(TTestTextUtils::Suite());
}
#pragma startup registerTests 33
