//---------------------------------------------------------------------------

#ifndef ENullPointerExceptionH
#define ENullPointerExceptionH

#include <vcl.h>
//---------------------------------------------------------------------------


class ENullPointerException : public Exception {
    private:
        UnicodeString stackTrace;

    public:
        ENullPointerException();
};


#endif
