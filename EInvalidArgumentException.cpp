//---------------------------------------------------------------------------

#pragma hdrstop

#include "EInvalidArgumentException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace CustomExceptions {
	EInvalidArgumentException::EInvalidArgumentException() : Exception("Invalid argument exception") {}
}