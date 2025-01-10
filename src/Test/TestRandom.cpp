#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>
#include <SysUtils.hpp>
#include <memory>

#include "Random.h"
#include "UnitTestLogger.h"


class TTestRandom : public TTestCase
{
	public:
		__fastcall virtual TTestRandom(System::String name) : TTestCase(name) {}
		virtual void __fastcall SetUp();
		virtual void __fastcall TearDown();

	__published:
		void __fastcall TestgetRandom();

};


void __fastcall TTestRandom::SetUp()
{
	LOGGER_CLEAR_LOG();
	LOGGER_LOG("Starting test...");

}

void __fastcall TTestRandom::TearDown()
{
	LOGGER_LOG("Test completed.");
    LOGGER_DISPLAY_LOG();
}


void __fastcall TTestRandom::TestgetRandom()
{
	for (int i = 0; i < 10; i++) {

        int result = Random::getRandom(0, 10);
        LOGGER_LOG("Test " + IntToStr(i + 1) + ": " + IntToStr(result));
        CheckTrue(result >= 0 && result <= 10, "Outside of range");
	}

}


static void registerTests()
{
  Testframework::RegisterTest(TTestRandom::Suite());
}
#pragma startup registerTests 33