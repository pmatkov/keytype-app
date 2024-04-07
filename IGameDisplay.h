//---------------------------------------------------------------------------

#ifndef IGameDisplayH
#define IGameDisplayH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.Classes.hpp>

__interface INTERFACE_UUID("{861C46F1-89D7-4EC8-8801-18823484DB46}") IGameDisplay : public IInterface {
    public:
		virtual void createTextControl(const UnicodeString& text, const UnicodeString& color) = 0;
		virtual void removeTextControl(int index) = 0;
		virtual void removeAllTextControls() = 0;
		virtual void moveTextControl(int index, int x, int y) = 0;

		virtual int getTextHeight(int index) = 0;
		virtual int getTextWidth(int index) = 0;

};

#endif
