 
//---------------------------------------------------------------------------
#ifndef WebModuleH
#define WebModuleH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.MySQL.hpp>
#include <FireDAC.Phys.MySQLDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
//---------------------------------------------------------------------------
class TWebModule1 : public TWebModule
{
__published:	// IDE-managed Components
	TFDConnection *MySQLDBConnection;
	TFDTable *TKeyMapping;
	TDataSource *DKeyMapping;
	TFDAutoIncField *TKeyMappingid;
	TIntegerField *TKeyMappingidRow;
	TIntegerField *TKeyMappingidCol;
	TStringField *TKeyMappingkeyValue;
	void __fastcall WebModule1DefaultHandlerAction(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled);
	void __fastcall WebModule1keymapGETAction(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled);
	void __fastcall WebModule1customtextGETAction(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled);
	void __fastcall WebModule1customtextPOSTAction(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled);
	void __fastcall WebModule1customtextPUTAction(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled);
	void __fastcall WebModuleBeforeDispatch(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled);
private:	// User declarations
public:		// User declarations
	__fastcall TWebModule1(TComponent* Owner);

    bool isAuthenticated(TWebRequest *Request, bool &Handled);
    bool isAuthorized(TWebRequest *Request, bool &Handled);
};
//---------------------------------------------------------------------------
extern PACKAGE TWebModule1 *WebModule1;
//---------------------------------------------------------------------------
#endif


