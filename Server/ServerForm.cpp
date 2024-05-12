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
    LConnectionStatusDisplay->Caption = "connection established";
}

void __fastcall TFServer::DMConnectionClosed(TObject *Sender)
{
    LConnectionStatusDisplay->Caption = "connection closed";
}

void __fastcall TFServer::BtTCPServer1Click(TObject *Sender)
{
    if (BtTCPServer1->Caption == "Start TCP Server1") {

    	BtTCPServer1->Caption = "Stop TCP Server1";
        dataModule->IdTCPServer->Active = true;
        LConnectionStatusDisplay->Caption = "waiting for connection..";

    }
    else if (BtTCPServer1->Caption == "Stop TCP Server1") {

    	BtTCPServer1->Caption = "Start TCP Server1";
        dataModule->IdTCPServer->Active = false;
        LConnectionStatusDisplay->Caption = "";

    }
}
//---------------------------------------------------------------------------

