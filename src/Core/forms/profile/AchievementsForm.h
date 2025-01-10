//---------------------------------------------------------------------------

#ifndef AchievementsFormH
#define AchievementsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include <vector>
#include <memory>

#include "AuthenticationService.h"
#include "DataModule.h"

//---------------------------------------------------------------------------
class TFAchievements : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
	AuthenticationService *authService;
	TDataModule1 *dataModule;

    std::unique_ptr<TLabel> LNoRecords;
	std::vector<std::unique_ptr<TLabel>> labels;
    std::vector<std::unique_ptr<TImage>> images;
public:		// User declarations
	__fastcall TFAchievements(TComponent* Owner);
    __fastcall TFAchievements(TComponent* Owner, AuthenticationService *_authService, TDataModule1 *_dataModule);

    void loadImageFromLibrary(const UnicodeString &resourceName);
    void displayNoRecord();
};
//---------------------------------------------------------------------------
extern PACKAGE TFAchievements *FAchievements;
//---------------------------------------------------------------------------
#endif
