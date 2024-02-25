//---------------------------------------------------------------------------

#pragma hdrstop

#include "ENullPointerException.h"
#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

ENullPointerException ::ENullPointerException() : Exception("Nullptr exception") {

     LOGGER(LogLevel::Fatal, "Nullptr exception");

}
