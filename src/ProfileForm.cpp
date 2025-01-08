//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProfileForm.h"
#include "FileUtils.h"
#include "UIUtils.h"
#include "CryptoUtils.h"
#include "Random.h"
#include "Logger.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFProfile *FProfile;
//---------------------------------------------------------------------------
__fastcall TFProfile::TFProfile(TComponent* Owner) : TForm(Owner)  {}

__fastcall TFProfile::TFProfile(TComponent* Owner, MainSession *_mainSession, AuthenticationService *_authService, TDataModule1 *_dataModule) : TForm(Owner)  {
     if (_authService && _mainSession && _dataModule) {

     	mainSession = _mainSession;
        authService = _authService;
    	dataModule = _dataModule;

        UIUtils::enableChildControls(GBProfile, false);

        DFileOpen->InitialDir = FileUtils::createAbsolutePath("Images", false);
    	DFileOpen->Filter = "Image Files(*jpg; *.png)|*.jpg;*.png";

       	LOGGER(LogLevel::Debug, "Created profile form");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }

}

void __fastcall TFProfile::FormActivate(TObject *Sender)
{
     if (mainSession && authService && dataModule) {

     	EAge->Alignment = taLeftJustify;

        // set active record in dataset

        dataModule->TUsers->Locate("username", authService->getUser().getUsername(), TLocateOptions());
     }
}

// edit profile

void __fastcall TFProfile::BtEditSaveClick(TObject *Sender)
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

        int userID;

        if (dataModule->TUsers->Locate("username", authService->getUser().getUsername(), TLocateOptions())) {

            userID = dataModule->TUsers->FieldByName("id")->AsInteger;
        }

        UnicodeString salt = CryptoUtils::generateSalt(EUsername->Text);
        UnicodeString hashedSalt = CryptoUtils::generateSHA256Hash(salt);

        UnicodeString oldPassword = dataModule->getColumnValue(dataModule->TUsers, "password", userID);
        UnicodeString password = EPassword->Text != "" ? CryptoUtils::generateSHA512Hash(IntToStr(Random::getRandom(1, 100)) + EPassword->Text + hashedSalt) : oldPassword;

        dataModule->TUsers->Edit();
        dataModule->TUsers->FieldByName("password")->AsString = password;
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


void __fastcall TFProfile::BtChangeImageClick(TObject *Sender)
{

    if (DFileOpen->Execute()) {

      if (FileExists(DFileOpen->FileName)) {

        std::unique_ptr<TFileStream> fileStream = std::make_unique<TFileStream>(DFileOpen->FileName, fmOpenRead);

        if (dataModule->TUsers && dataModule->TUsers->Active && !dataModule->TUsers->IsEmpty()) {

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

}

void __fastcall TFProfile::BtDeleteImageClick(TObject *Sender)
{
    dataModule->TUsers->Edit();
    dataModule->TUsers->FieldByName("profileImage")->Clear();
    dataModule->TUsers->Post();

}

// delete profile

void __fastcall TFProfile::BtDeleteClick(TObject *Sender)
{

	dataModule->TUsers->Delete();

    if (mainSession->getAppSettings().getLanguage() == Language::English) {
    	UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Profile deleted");
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
    	UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Profil obrisan");

    }
}



void __fastcall TFProfile::msgDisplayTimerTimer(TObject *Sender)
{
	UIUtils::removeTimedMessage(msgDisplayTimer, LInfo);
}
//---------------------------------------------------------------------------

