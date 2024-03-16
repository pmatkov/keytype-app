//---------------------------------------------------------------------------

#pragma hdrstop

#include "EFileNotFoundException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace CustomExceptions {
	EFileNotFoundException::EFileNotFoundException() : EIOException("File not found exception") {}
}
