//---------------------------------------------------------------------------

#ifndef EInvalidArgumentExceptionH
#define EInvalidArgumentExceptionH

#include <vcl.h>

//---------------------------------------------------------------------------

namespace CustomExceptions {

    class EInvalidArgumentException : public Exception {
        public:
            EInvalidArgumentException();
    };
}
#endif
