//---------------------------------------------------------------------------

#ifndef MainFrameH
#define MainFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFrMain : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LLogo;
private:	// User declarations
public:		// User declarations
	__fastcall TFrMain(TComponent* Owner);
    void setLogo();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrMain *FrMain;
//---------------------------------------------------------------------------
#endif
