//---------------------------------------------------------------------------

#ifndef CustomTextFrameH
#define CustomTextFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XmlTransform.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
//---------------------------------------------------------------------------
class TFrCustomText : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TFrCustomText(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrCustomText *FrCustomText;
//---------------------------------------------------------------------------
#endif
