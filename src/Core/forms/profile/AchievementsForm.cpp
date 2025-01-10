//---------------------------------------------------------------------------
#undef UNICODE
#define UNICODE

#include <vcl.h>
#pragma hdrstop

#include "AchievementsForm.h"
#include "AchievementsUtils.h"
#include "FileUtils.h"
#include "EnumUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define DEF_MARGIN 30
#define DEF_IMAGE_WIDTH 18
#define DEF_IMAGE_HEIGHT 18
#define DEF_LABEL_HEIGHT 15
#define DEF_LABEL_POS() ((DEF_IMAGE_HEIGHT/ 2 - DEF_LABEL_HEIGHT/ 2) < 0 ? 0 : (DEF_IMAGE_HEIGHT / 2 - DEF_LABEL_HEIGHT / 2))


TFAchievements *FAchievements;
//---------------------------------------------------------------------------
__fastcall TFAchievements::TFAchievements(TComponent* Owner) : TForm(Owner) {}

__fastcall TFAchievements::TFAchievements(TComponent* Owner,  AuthenticationService *_authService, TDataModule1 *_dataModule) : TForm(Owner) {

	if (_authService && _dataModule) {

       authService = _authService;
       dataModule = _dataModule;

       LOGGER(LogLevel::Debug, "Created achievements form");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFAchievements::loadImageFromLibrary(const UnicodeString &resourceName) {

    // load ResourceLib.dll

	HINSTANCE Resource;

    if ((Resource = LoadLibrary(L"ResourceLib.dll")) == nullptr) {
        ShowMessage("Can't load DLL");
		return;
    }

    std::unique_ptr<TResourceStream> resStream = std::make_unique<TResourceStream>((int)Resource, resourceName, RT_RCDATA);

	images.push_back(std::make_unique<TImage>(this));
    images[images.size()-1]->Parent = this;
	images[images.size()-1]->Width = DEF_IMAGE_WIDTH;
	images[images.size()-1]->Height = DEF_IMAGE_HEIGHT;
	images[images.size()-1]->Top = images.size() > 1 ? images[images.size()-2]->Top + 2 * DEF_IMAGE_HEIGHT : DEF_IMAGE_HEIGHT;
	images[images.size()-1]->Left = DEF_MARGIN;
    images[images.size()-1]->Picture->LoadFromStream(resStream.get());


    FreeLibrary(Resource);
}

void TFAchievements::displayNoRecord() {

	LNoRecords = std::make_unique<TLabel>(this);
    LNoRecords->Parent = this;
    LNoRecords->Top = 150;
    LNoRecords->Left = 170;
    LNoRecords->Caption = "No achievements recorded";
    LNoRecords->Visible = true;
}


void __fastcall TFAchievements::FormActivate(TObject *Sender)
{
   std::vector<AchievementsRecord> records = AchievementsUtils::readFromFile(FileUtils::createProjectSubDirPath("Data") + "achievements");

   bool noRecords = false;

   if (records.size()) {

     if (dataModule->TUsers->Locate("username", authService->getUser().getUsername(), TLocateOptions())) {

		int idUser = dataModule->TUsers->FieldByName("id")->AsInteger;

        std::vector<AchievementsRecord> filteredRecords = AchievementsUtils::filterAchievements(records, idUser);

        if (filteredRecords.size()) {

            if (LNoRecords) {
                LNoRecords.reset();
            }

            for (const AchievementsRecord &record: filteredRecords) {

                UnicodeString title = record.getTitle();
                UnicodeString description = record.getDescription();
                UnicodeString date = FormatDateTime("dd/mm/yyyy", record.getDate());

                labels.push_back(std::make_unique<TLabel>(this));
                labels[labels.size()-1]->Parent = this;
				labels[labels.size()-1]->Top = labels.size() > 1 ? labels[labels.size()-2]->Top + DEF_IMAGE_HEIGHT + DEF_LABEL_POS() : DEF_IMAGE_HEIGHT + DEF_LABEL_POS();
				labels[labels.size()-1]->Left = DEF_MARGIN + DEF_IMAGE_WIDTH + DEF_MARGIN/ 2;
                labels[labels.size()-1]->Caption = title + " - " + description + " - " + date;

				UnicodeString image = "";

                if (title == "SpeedMaster") {
                    image = "PngImage_6";
                }
                else if (title == "PerfectScore") {
                    image = "PngImage_3";
                }

                // display achievement image

                loadImageFromLibrary(image);
            }
        }

        else {
            noRecords = true;
        }

    }
   }
   else {
    noRecords = true;
   }

   if (noRecords) {
      displayNoRecord();
   }


}
//---------------------------------------------------------------------------
