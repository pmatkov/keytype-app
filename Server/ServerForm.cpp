//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ServerForm.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFServer *FServer;
//---------------------------------------------------------------------------
__fastcall TFServer::TFServer(TComponent* Owner) : TForm(Owner), logger(Logger::getLogger())  {}

void TFServer::setDataModule(TDataModule2 *_dataModule) {

    if (_dataModule) {
      	dataModule = _dataModule;
        dataModule->OnConnectionEstablished = DMConnectionEstablished;
        dataModule->OnConnectionClosed = DMConnectionClosed;
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFServer::DMConnectionEstablished(TObject *Sender)
{
    LTCPConnectionStatus->Caption = "connection established";
}

void __fastcall TFServer::DMConnectionClosed(TObject *Sender)
{
    LTCPConnectionStatus->Caption = "connection closed";
}

void __fastcall TFServer::BtTCPServerClick(TObject *Sender)
{
    if (BtTCPServer->Caption == "Start TCP Server") {

    	BtTCPServer->Caption = "Stop TCP Server";
        dataModule->IdTCPServer->Active = true;
        LTCPConnectionStatus->Caption = "waiting for connection..";

    }
    else if (BtTCPServer->Caption == "Stop TCP Server") {

    	BtTCPServer->Caption = "Start TCP Server";
        dataModule->IdTCPServer->Active = false;
        LTCPConnectionStatus->Caption = "";

    }
}

void __fastcall TFServer::BtUDPServerClick(TObject *Sender)
{
   	if (BtUDPServer->Caption == "Start UDP server") {

    	BtUDPServer->Caption = "Stop UDP server";
        dataModule->IdUDPServer->Active = true;
        LUDPServerStatus->Caption = "started..";

    }
    else if (BtUDPServer->Caption == "Stop UDP server") {

    	BtUDPServer->Caption = "Start UDP server";
        dataModule->IdUDPServer->Active = false;
        LUDPServerStatus->Caption = "";

    }
}
//---------------------------------------------------------------------------

