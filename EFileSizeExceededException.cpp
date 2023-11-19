//---------------------------------------------------------------------------


#include "EFileSizeExceededException.h"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

EFileSizeExceededException::EFileSizeExceededException(int _size, int _limit) : Exception(""), size(_size), limit(_limit) {}

void EFileSizeExceededException::displayMessage() {

	ShowMessage("File size " + IntToStr(size) + " B exceeds the allowed limit of " + IntToStr(limit) + " B.");
}
