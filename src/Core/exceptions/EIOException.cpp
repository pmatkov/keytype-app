//---------------------------------------------------------------------------

#pragma hdrstop

#include "EIOException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

EIOException::EIOException() : Exception("IO exception") {}

EIOException::EIOException(const UnicodeString &message) : Exception(message) {}

const UnicodeString &EIOException::getMessage() const {
    return message;
}
