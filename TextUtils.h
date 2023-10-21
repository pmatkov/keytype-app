//---------------------------------------------------------------------------

#ifndef TextUtilsH
#define TextUtilsH

#include <vcl.h>
#include <windows.h>

class TextUtils
{
public:
	static char getDisplayableChar(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
//---------------------------------------------------------------------------
#endif
