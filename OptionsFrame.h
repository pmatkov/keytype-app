//---------------------------------------------------------------------------

#ifndef OptionsFrameH
#define OptionsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Buttons.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TFrOptions : public TFrame
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TButton *FrButtonOptions;
private:	// User declarations
public:		// User declarations
	__fastcall TFrOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrOptions *FrOptions;
//---------------------------------------------------------------------------
#endif
