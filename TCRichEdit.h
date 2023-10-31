//---------------------------------------------------------------------------

#ifndef TRichEditH
#define TRichEditH
//---------------------------------------------------------------------------

#include <Vcl.ComCtrls.hpp>

class TCRichEdit : public TRichEdit
{
	protected:
	void __fastcall OnMouseEnter(TObject *Sender);
	void __fastcall OnMouseLeave(TObject *Sender);
	void __fastcall OnClick(TObject *Sender);
	void __fastcall OnDblClick(TObject *Sender);
	void __fastcall OnEnter(TObject *Sender);
	void __fastcall OnExit(TObject *Sender);

	public:
       __fastcall TCRichEdit(TComponent* AOwner);
};



#endif
