//---------------------------------------------------------------------------


#include "EFileSizeExceededException.h"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

EFileSizeExceededException::EFileSizeExceededException(int size, int limit) : Exception("File size " + IntToStr(size) + " B exceeds the allowed limit of " + IntToStr(limit) + " B.") {}

