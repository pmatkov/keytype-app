//---------------------------------------------------------------------------

#pragma hdrstop

#include "EDirNotFoundException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace CustomExceptions {
	EDirNotFoundException::EDirNotFoundException() : EIOException("Directory not found exception") {}
}
