//---------------------------------------------------------------------------

#ifndef KeyboardFrameH
#define KeyboardFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include <vector>
#include <memory>

#include "DataModule.h"
#include "MainSession.h"
#include "ColorButton.h"

//---------------------------------------------------------------------------
class TFrKeyboard : public TFrame
{
__published:	// IDE-managed Components
	TPanel *PKeyboardBase;
private:	// User declarations
    TDataModule1 *dataModule;
    MainSession *mainSession;
 	std::vector<std::unique_ptr<TColorButton>> buttons;

public:		// User declarations
	__fastcall TFrKeyboard(TComponent* Owner);

    void setDataModule(TDataModule1 *_dataModule);
    void setMainSession(MainSession *_mainSession);

    void generateKeyboardLayout();
    void generateKeyboardRow(TWinControl* parent, int xPos, int yPos, const std::vector<UnicodeString> &captions);
    void initializeColorButton(TColorButton* button, TWinControl* parent, TColor bgColor, TColor fgColor, int width, int height, const UnicodeString& caption);

    void highlightKey(const UnicodeString& caption, bool setColor);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrKeyboard *FrKeyboard;
//---------------------------------------------------------------------------
#endif
