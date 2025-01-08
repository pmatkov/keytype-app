//---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>

#include <optional>
#include <vector>

//---------------------------------------------------------------------------
class TDataModule2 : public TDataModule
{
__published:	// IDE-managed Components
	TIdTCPServer *IdTCPServer;
	TIdUDPServer *IdUDPServer;
	void __fastcall IdTCPServerExecute(TIdContext *AContext);
	void __fastcall IdTCPServerConnect(TIdContext *AContext);
	void __fastcall IdTCPServerDisconnect(TIdContext *AContext);
	void __fastcall IdUDPServerUDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding);
private:	// User declarations

public:		// User declarations
	__fastcall TDataModule2(TComponent* Owner);
    void __fastcall (__closure *OnConnectionEstablished)(TObject *Sender);
    void __fastcall (__closure *OnConnectionClosed)(TObject *Sender);

    std::optional<UnicodeString> generateJsonFromWordList(const std::vector<UnicodeString> &wordList);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataModule2 *DataModule2;
//---------------------------------------------------------------------------
#endif
