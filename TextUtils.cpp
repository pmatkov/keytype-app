//---------------------------------------------------------------------------

#include "TextUtils.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)


// detect if a key was pressed and if it represents a displayable character
char TextUtils::getDisplayableChar(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CHAR)
		return wParam;
	else
        return 0;

}

