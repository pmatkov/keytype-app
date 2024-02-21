//---------------------------------------------------------------------------

#pragma hdrstop

#include "Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Session::Session() {
    sessionUuid = UUIDGenerator::generateUUID();
}

Session::~Session() {}

