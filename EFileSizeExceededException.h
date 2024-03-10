//---------------------------------------------------------------------------

#ifndef EFileSizeExceededExceptionH
#define EFileSizeExceededExceptionH

#include <System.SysUtils.hpp>
#include <vcl.h>

//---------------------------------------------------------------------------

class EFileSizeExceededException : public Exception {

	public:
		EFileSizeExceededException(int _size, int _limit);


};

#endif
