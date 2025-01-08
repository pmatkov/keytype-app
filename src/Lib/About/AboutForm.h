//---------------------------------------------------------------------------

#ifndef AboutFormH
#define AboutFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#if EXPORTS
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

//---------------------------------------------------------------------------
class TFAbout : public TForm
{
__published:	// IDE-managed Components
	TLabel *LVersion;
	TLabel *LCreated;
	TButton *BtOk;
private:	// User declarations
public:		// User declarations
	__fastcall TFAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern "C" void DLL_EXPORT __stdcall CreateAboutForm();
extern PACKAGE TFAbout *FAbout;
//---------------------------------------------------------------------------
#endif
