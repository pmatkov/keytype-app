//---------------------------------------------------------------------------

#ifndef UnitTestLoggerH
#define UnitTestLoggerH

#include <vcl.h>
#include <System.hpp>
#include <TestFramework.hpp>
#include <SysUtils.hpp>

class UnitTestLogger
{
	private:
		TStringList* logList;

	public:
		UnitTestLogger();
		~UnitTestLogger();

		TStringList* getLogStringList() const;
		void log(const UnicodeString& text);

};


//---------------------------------------------------------------------------
#endif
