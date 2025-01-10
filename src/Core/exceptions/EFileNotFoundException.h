//---------------------------------------------------------------------------

#ifndef EFileNotFoundExceptionH
#define EFileNotFoundExceptionH

#include "EIOException.h"
//---------------------------------------------------------------------------

namespace CustomExceptions {

    class EFileNotFoundException : public EIOException {
        public:
            EFileNotFoundException();
    };
}
#endif
