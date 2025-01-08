//---------------------------------------------------------------------------

#ifndef ServerFormH
#define ServerFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "DataModule.h"
#include "Logger.h"

class TFServer : public TForm
{
__published:	// IDE-managed Components
	TButton *BtTCPServer;
	TLabel *LTCPConnectionStatus;
	TLabel *LUDPServerStatus;
	TButton *BtUDPServer;
	void __fastcall BtTCPServerClick(TObject *Sender);
	void __fastcall BtUDPServerClick(TObject *Sender);
private:	// User declarations
	TDataModule2 *dataModule;
    Logger &logger;
public:		// User declarations
	__fastcall TFServer(TComponent* Owner);
    void setDataModule(TDataModule2 *_dataModule);
    void __fastcall DMConnectionEstablished(TObject *Sender);
    void __fastcall DMConnectionClosed(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TFServer *FServer;
//---------------------------------------------------------------------------
#endif

