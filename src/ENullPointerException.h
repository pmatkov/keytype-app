//---------------------------------------------------------------------------

#ifndef ENullPointerExceptionH
#define ENullPointerExceptionH

#include <vcl.h>
//---------------------------------------------------------------------------

namespace CustomExceptions {

    class ENullPointerException : public Exception {
        public:
            ENullPointerException();
    };
}

#endif
