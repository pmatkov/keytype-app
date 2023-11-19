//---------------------------------------------------------------------------

#ifndef EFileSizeExceededExceptionH
#define EFileSizeExceededExceptionH

#include <System.SysUtils.hpp>
#include <vcl.h>

//---------------------------------------------------------------------------

class EFileSizeExceededException : public Exception {

	private:
		int size;
		int limit;

	public:
		EFileSizeExceededException(int _size, int _limit);
		void displayMessage();

};

#endif
