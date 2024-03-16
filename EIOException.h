//---------------------------------------------------------------------------

#ifndef EIOExceptionH
#define EIOExceptionH
//---------------------------------------------------------------------------

#include "vcl.h"

class EIOException: Exception {

    private:
    	UnicodeString message = "";

    public:
    	EIOException();
        EIOException(const UnicodeString &message);
        const UnicodeString &getMessage() const;
};


#endif
