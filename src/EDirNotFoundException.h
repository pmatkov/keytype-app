//---------------------------------------------------------------------------

#ifndef EDirNotFoundExceptionH
#define EDirNotFoundExceptionH

#include "EIOException.h"
//---------------------------------------------------------------------------

namespace CustomExceptions {

    class EDirNotFoundException : public EIOException {
        public:
            EDirNotFoundException();
    };
}
#endif
