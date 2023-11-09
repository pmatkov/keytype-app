//---------------------------------------------------------------------------

#ifndef LoggerH
#define LoggerH

#include <vcl.h>
#include <System.hpp>
#include <TestFramework.hpp>
#include <SysUtils.hpp>

class Logger
{
	private:
		TStringList* logStringList;

	public:
		Logger();
		~Logger();

		TStringList* getLogStringList() const;
		void log(const UnicodeString& text);

};


//---------------------------------------------------------------------------
#endif
