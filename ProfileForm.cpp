//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProfileForm.h"
#include "FileUtils.h"
#include "UIUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrProfile *FrProfile;
//---------------------------------------------------------------------------
__fastcall TFrProfile::TFrProfile(TComponent* Owner) : TForm(Owner)  {}

__fastcall TFrProfile::TFrProfile(TComponent* Owner, MainSession *_mainSession, AuthenticationService *_authService, TDataModule1 *_dataModule) : TForm(Owner)  {
     if (_authService && _mainSession && _dataModule) {

     	mainSession = _mainSession;
        authService = _authService;
    	dataModule = _dataModule;

        UIUtils::enableChildControls(GBProfile, false);

        DFileOpen->InitialDir = FileUtils::createAbsolutePath("Images", false);
    	DFileOpen->Filter = "Image Files(*jpg; *.png)|*.jpg;*.png";

       	LOGGER(LogLevel::Debug, "View profile displayed");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }


}

void __fastcall TFrProfile::BtEditSaveClick(TObject *Sender)
{
	if (BtEditSave->Caption == "Edit profile" || BtEditSave->Caption == "Uredi profil") {

        UIUtils::enableChildControls(GBProfile, true);

        if (mainSession->getAppSettings().getLanguage() == Language::English) {
        	BtEditSave->Caption = "Save profile";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
             BtEditSave->Caption = "Spremi profil";
        }
    }
     else if (BtEditSave->Caption == "Save profile" || BtEditSave->Caption == "Spremi profil") {

     	if (dataModule->TUsers->Locate("username; password", VarArrayOf(OPENARRAY(Variant, (authService->getUser().getUsername(), authService->getUser().getPassword()))), TLocateOptions())) {

        	int userID = dataModule->TUsers->FieldByName("id")->AsInteger;

            if (EUsername->Text != dataModule->getColumnValue(dataModule->TUsers, "username", userID)) {

                if (dataModule->TUsers->Locate("username", authService->getUser().getUsername(), TLocateOptions())) {
                    ShowMessage("Username already registered.");
                    return ;
                }
            }
        }
        dataModule->TUsers->Edit();
     	dataModule->TUsers->FieldByName("username")->AsString = EUsername->Text;
     	dataModule->TUsers->FieldByName("password")->AsString = EPassword->Text;
     	dataModule->TUsers->FieldByName("name")->AsString = EName->Text;
     	dataModule->TUsers->FieldByName("surname")->AsString = ESurname->Text;
     	dataModule->TUsers->FieldByName("email")->AsString = EEmail->Text;

        if (!EAge->Text.IsEmpty()) {
        	dataModule->TUsers->FieldByName("age")->AsInteger = StrToInt(EAge->Text);
        }
        else {
             dataModule->TUsers->FieldByName("age")->Clear();
        }

    	dataModule->TUsers->Post();

        if (mainSession->getAppSettings().getLanguage() == Language::English) {
    		UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Profile saved");
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Profil spremljen");

        }

        UIUtils::enableChildControls(GBProfile, false);

        if (mainSession->getAppSettings().getLanguage() == Language::English) {
        	BtEditSave->Caption = "Edit profile";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
             BtEditSave->Caption = "Uredi profil";
        }


     }
}
//---------------------------------------------------------------------------
void __fastcall TFrProfile::BtChangeImageClick(TObject *Sender)
{

    if (DFileOpen->Execute()) {

      if (FileExists(DFileOpen->FileName)) {

        std::unique_ptr<TFileStream> fileStream = std::make_unique<TFileStream>(DFileOpen->FileName, fmOpenRead);

        dataModule->TUsers->Edit();

        try {
            std::unique_ptr<TStream> blobStream(dataModule->TUsers->CreateBlobStream(dataModule->TUsers->FieldByName("profileImage"), bmWrite));
            blobStream->CopyFrom(fileStream.get(), fileStream->Size);
            blobStream.reset();
            dataModule->TUsers->Post();
        }
        catch (const Exception &) {
            dataModule->TUsers->Cancel();
            throw;
        }
      }
    }

}

void __fastcall TFrProfile::BtDeleteImageClick(TObject *Sender)
{
	dataModule->TUsers->Edit();
    dataModule->TUsers->FieldByName("profileImage")->Clear();
    dataModule->TUsers->Post();

}
//---------------------------------------------------------------------------

void __fastcall TFrProfile::BtDeleteClick(TObject *Sender)
{
	dataModule->TUsers->Delete();

    if (mainSession->getAppSettings().getLanguage() == Language::English) {
    	UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Profile deleted");
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
    	UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Profil obrisan");

    }
}

void __fastcall TFrProfile::FormActivate(TObject *Sender)
{
     if (authService && mainSession && dataModule) {

     	EAge->Alignment = taLeftJustify;
        dataModule->TUsers->Locate("username; password", VarArrayOf(OPENARRAY(Variant, (authService->getUser().getUsername(), authService->getUser().getPassword()))), TLocateOptions());
     }
}


void __fastcall TFrProfile::msgDisplayTimerTimer(TObject *Sender)
{
	UIUtils::removeTimedMessage(msgDisplayTimer, LInfo);
}
//---------------------------------------------------------------------------

