//---------------------------------------------------------------------------

#pragma hdrstop

#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace CustomExceptions {
	ENullPointerException::ENullPointerException() : Exception("Null pointer exception") {}
}
