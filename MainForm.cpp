//---------------------------------------------------------------------------
#undef UNICODE
#define UNICODE

#include "MainForm.h"

#include <System.DateUtils.hpp>

#include "UIUtils.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "ENullPointerException.h"
#include "GameThread.h"

#include "KeyStatistics.h"
#include "DLL\\UserStatistics.h"
#include "DLL\\StatisticsForm.h"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma link "MainFrame"
#pragma link "PracticeFrame"
#pragma resource "*.dfm"

TFMain *FMain;

__fastcall TFMain::TFMain(TComponent* Owner) : TForm(Owner), logger(Logger::getLogger())  {

	FrMain = UIUtils::createFrame<TFrMain>(this);
	UIUtils::setFrameVisibility<TFrMain>(FrMain, true);

	LOGGER(LogLevel::Debug, "Created main form");
}

void TFMain::setDataModule(TDataModule1 *_dataModule) {

    if (_dataModule) {
      	dataModule = _dataModule;
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFMain::setMainSession(std::unique_ptr<MainSession> _mainSession) {

    if (_mainSession) {
      	mainSession = std::move(_mainSession);

        logger.setMainSession(mainSession.get());

		UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());
        UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());

       	LOGGER(LogLevel::Debug, "Main session moved");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFMain::setAuthenticationService(std::unique_ptr<AuthenticationService> _authService) {

    if (_authService) {
      	authService = std::move(_authService);

        updateProfileMenu();

       	LOGGER(LogLevel::Debug, "Authentication service moved");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFMain::setAuthenticationForm(std::unique_ptr<TFAuthentication> _FAuthentication) {

    if (_FAuthentication) {
      	FAuthentication = std::move(_FAuthentication);

       	LOGGER(LogLevel::Debug, "Authentication form moved");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}


// dispatch char messages for processing

void __fastcall TFMain::WndProc(Messages::TMessage &Message) {

    switch (Message.Msg) {

        case WM_CHAR: {

            if (FrPractice && FrPractice->Visible) {
                FrPractice->processCharMessages(Message.WParam);
            }
            else if (FrFlyingWords && FrFlyingWords->Visible) {
            	FrFlyingWords->processCharMessages(Message.WParam);
            }
            else if (FrLessons2 && FrLessons2->Visible) {
            	FrLessons2->processCharMessages(Message.WParam);
            }
            break;
        }
        default: {
            TForm::WndProc(Message);
        }
	}
}

void __fastcall TFMain::MenuSubitemPracticeNewClick(TObject *Sender)
{

	if (!typingSession) {
       typingSession = std::make_unique<TypingSession>();
    }

    if (!parser) {
        parser = std::make_unique<Parser>(mainSession.get(), typingSession.get());
    }

    if (!FrPractice) {
		FrPractice = UIUtils::createFrame<TFrPractice>(this, dataModule, parser.get(), mainSession.get(), typingSession.get());

        //  set subclass procedure for REText
		SetWindowSubclass(FrPractice->FrTypingText->REText->Handle, &FrPractice->FrTypingText->RESubclass, 0, 0);
	}

	if (FrMain && FrMain->Visible) {
		UIUtils::switchFrames<TFrMain, TFrPractice>(FrMain, FrPractice);
	}
    else if (FrLessons2 && FrLessons2->Visible) {
		UIUtils::switchFrames<TFrLessons2, TFrPractice>(FrLessons2, FrPractice);
	}

    // terminate thread and cleanup
	else if (FrFlyingWords && FrFlyingWords->Visible) {

    	FrFlyingWords->getGameEngine().threadTerminate();
        FrFlyingWords->getGameEngine().gameCleanup();
		UIUtils::switchFrames<TFrFlyingWords, TFrPractice>(FrFlyingWords, FrPractice);
	}
}

void __fastcall TFMain::MenuSubitemPreferencesClick(TObject *Sender)
{

	if (!FPreferences) {
		FPreferences = std::make_unique<TFPreferences>(nullptr, mainSession.get(), authService.get());
		FPreferences->Position = poMainFormCenter;
	}

    if (typingSession) {
		typingSession->setSessionStatus(SessionStatus::Paused);
		FrPractice->FrTypingText->setTypingStatus(SessionStatus::Paused);

        FrPractice->FrTypingText->clearCaret(mainSession->getTypingSettings().getCaretType(), typingSession->getTextSource().getCharIndex()-1);
        parser->setInputEnabled(false);
    }

    if (FPreferences->ShowModal() == mrOk) {

        if (mainSession->getAppSettings().getLanguageChanged()) {
            UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());
            mainSession->getAppSettings().setLanguageChanged(false);
        }

        if (typingSession) {
            typingSession->setSessionStatus(SessionStatus::Initialized);
            FrPractice->FrTypingText->setTypingStatus(SessionStatus::Initialized);
        }
    }
}

void __fastcall TFMain::MenuSubitemFlyingWordsClick(TObject *Sender)
{
	if (!FrFlyingWords) {
		FrFlyingWords = UIUtils::createFrame<TFrFlyingWords>(this);
	}

	if (FrMain && FrMain->Visible) {
		UIUtils::switchFrames<TFrMain, TFrFlyingWords>(FrMain, FrFlyingWords);
	}
	else if (FrPractice && FrPractice->Visible) {
		UIUtils::switchFrames<TFrPractice, TFrFlyingWords>(FrPractice, FrFlyingWords);
	}
    else if (FrLessons2 && FrLessons2->Visible) {
		UIUtils::switchFrames<TFrLessons2, TFrFlyingWords>(FrLessons2, FrFlyingWords);
	}
}

void __fastcall TFMain::MenuSubItemConfigurationClick(TObject *Sender)
{
   	if (!FLessons) {
		FLessons = std::make_unique<TFLessons>(nullptr, dataModule);
        FLessons->Position = poMainFormCenter;
	}

 	if (FLessons->ShowModal() == mrOk) {

		//
    }
}
//---------------------------------------------------------------------------

void __fastcall TFMain::MenuSubItemLessonStartClick(TObject *Sender)
{
  	if (!typingSession) {
       typingSession = std::make_unique<TypingSession>();
    }
    if (!parser) {
        parser = std::make_unique<Parser>(mainSession.get(), typingSession.get());
    }
    if (!FrLessons2) {

		FrLessons2 = UIUtils::createFrame<TFrLessons2>(this, parser.get(), mainSession.get(), typingSession.get(), authService.get(), dataModule);

        //  set subclass procedure for REText
		SetWindowSubclass(FrLessons2->FrTypingText->REText->Handle, &FrLessons2->FrTypingText->RESubclass, 0, 0);
	}

	if (FrMain && FrMain->Visible) {
		UIUtils::switchFrames<TFrMain, TFrLessons2>(FrMain, FrLessons2);
	}

    // terminate thread and cleanup
	else if (FrFlyingWords && FrFlyingWords->Visible) {

    	FrFlyingWords->getGameEngine().threadTerminate();
        FrFlyingWords->getGameEngine().gameCleanup();
		UIUtils::switchFrames<TFrFlyingWords, TFrLessons2>(FrFlyingWords, FrLessons2);
	}
}


void __fastcall TFMain::MenuSubItemLessonResultsClick(TObject *Sender)
{
	if (!FLessonResults) {
		FLessonResults = std::make_unique<TFLessonResults>(nullptr, dataModule);
        FLessonResults->Position = poMainFormCenter;
	}
    if (FLessonResults->ShowModal() == mrOk) {

		//
    }
}


void __fastcall TFMain::MenuSubItemViewProfileClick(TObject *Sender) {

	if (!FrProfile) {

		FrProfile = std::make_unique<TFrProfile>(this,  mainSession.get(), authService.get(), dataModule);
        FrProfile->Position = poMainFormCenter;

	}
    FrProfile->ShowModal();
}

void __fastcall TFMain::MenuSubItemViewStatisticsClick(TObject *Sender) {

	if (!FStatistics) {

    	std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
        std::map<wchar_t, KeyStatistics> keyStatistics;
        std::vector<TDateTime> practiceTime;

        try {

            query->Connection = dataModule->MySQLDBConnection;
            UnicodeString username = authService->getUser().getUsername();

            query->SQL->Text = "SELECT `key`, SUM(correct) AS sumCorrect, SUM(mistake) AS sumMistake FROM keystatistics JOIN lessonresults \
             ON keystatistics.idLessonResults = lessonresults.id JOIN users ON lessonresults.idUser = users.id \
            WHERE username = :username GROUP BY `key` ORDER BY `key` ASC";

            query->Params->ParamByName("username")->AsString = username;
            query->Open();

            if (!query->IsEmpty()) {

            	while (!query->Eof) {
                    wchar_t key = query->FieldByName("key")->AsString[1];
                    int sumCorrect = query->FieldByName("sumCorrect")->AsInteger;
                    int sumMistake = query->FieldByName("sumMistake")->AsInteger;

                    keyStatistics[key] = KeyStatistics(key, sumCorrect, sumMistake);

                    query->Next();
                }
            }

            query->Close();

            query->SQL->Text = "SELECT `date`, SUM(duration) AS sumDuration FROM lessonresults \
            JOIN users ON lessonresults.idUser = users.id \
            WHERE username = :username GROUP BY `date` ORDER BY `date` ASC";

            query->Params->ParamByName("username")->AsString = username;
            query->Open();

            if (!query->IsEmpty()) {

            	while (!query->Eof) {

                 	TDateTime tDate = query->FieldByName("date")->AsDateTime;

            		unsigned short year, month, day;
                    DecodeDate(tDate, year, month, day);

                    int totalDuration = query->FieldByName("sumDuration")->AsInteger;
                	unsigned short hrs = totalDuration / 3600;
                    unsigned short min = (totalDuration % 3600) / 60;
                    unsigned short sec = totalDuration % 60;

                    practiceTime.push_back(EncodeDateTime(year, month, day, hrs, min, sec, 0));

                    query->Next();
                }

            }
          query->Close();

        } catch (Exception &ex) {
            LOGGER(LogLevel::Fatal, ex.Message);
        }


    	HINSTANCE Statistics;

        if ((Statistics = LoadLibrary(L"StatisticsLib.dll")) == nullptr) {
            ShowMessage("Can't load DLL");
            return;
        }

        typedef UserStatistics*(*__stdcall pCreateUserStatistics)(const std::vector<TDateTime>&, const std::map<wchar_t, KeyStatistics>&);
        pCreateUserStatistics CreateUserStatistics;

        if ((CreateUserStatistics = (pCreateUserStatistics)GetProcAddress(Statistics, "CreateUserStatistics")) == nullptr) {
            ShowMessage("Can't find CreateUserStatistics function");
            return;
        }

    	userStatistics = CreateUserStatistics(practiceTime, keyStatistics);

		typedef TFStatistics*(*__stdcall pCreateStatisticsForm)(UserStatistics *userStatistics);
        pCreateStatisticsForm CreateStatisticsForm;

        if ((CreateStatisticsForm = (pCreateStatisticsForm)GetProcAddress(Statistics, "CreateStatisticsForm")) == nullptr) {
            ShowMessage("Can't find CreateStatisticsForm function");
            return;
        }

   		CreateStatisticsForm(userStatistics);
        FreeLibrary(Statistics);
	}
}


void __fastcall TFMain::MenuSubItemDeleteProfileClick(TObject *Sender) {

	if (dataModule->TUsers->Locate("username; password", VarArrayOf(OPENARRAY(Variant, (authService->getUser().getUsername(), authService->getUser().getPassword()))), TLocateOptions())) {
		dataModule->TUsers->Delete();
    }
    authService->loginUser("guest", "");
    updateProfileMenu();

}

void __fastcall TFMain::MenuSubItemSwitchUserClick(TObject *Sender) {


	if (!FAuthentication) {

       FAuthentication = std::make_unique<TFAuthentication>(nullptr, authService.get());
	}
    FAuthentication->Position = poMainFormCenter;

    if (FAuthentication->ShowModal() == mrOk) {

        updateProfileMenu();
    }
}
void TFMain::updateProfileMenu() {


    if (!menuItemProfile) {
    	menuItemProfile = std::make_unique<TMenuItem>(MainMenu);
        MainMenu->Items->Add(menuItemProfile.get());
    }

    if (!menuSubItemViewProfile) {
    	menuSubItemViewProfile = std::make_unique<TMenuItem>(MainMenu);
        menuSubItemViewProfile->OnClick = MenuSubItemViewProfileClick;
    	menuItemProfile->Add(menuSubItemViewProfile.get());
    }

    if (mainSession->getAppSettings().getLanguage() == Language::English) {
    	menuSubItemViewProfile->Caption = "View profile";
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
        menuSubItemViewProfile->Caption = "Pregledaj profil";
    }

    UnicodeString projectExePath = ExtractFilePath(Application->ExeName);

    if (FileUtils::checkFileExistance(projectExePath + "StatisticsLib.dll")) {

        if (!menuSubItemViewStatistics) {
            menuSubItemViewStatistics = std::make_unique<TMenuItem>(MainMenu);
            menuSubItemViewStatistics->OnClick = MenuSubItemViewStatisticsClick;
            menuItemProfile->Add(menuSubItemViewStatistics.get());
        }
        if (mainSession->getAppSettings().getLanguage() == Language::English) {
            menuSubItemViewStatistics->Caption = "View statistics";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            menuSubItemViewStatistics->Caption = "Pregledaj statistiku";
        }
    }

    if (!menuSubItemDeleteProfile) {
    	menuSubItemDeleteProfile = std::make_unique<TMenuItem>(MainMenu);
        menuSubItemDeleteProfile->OnClick = MenuSubItemDeleteProfileClick;
    	menuItemProfile->Add(menuSubItemDeleteProfile.get());
    }

    if (mainSession->getAppSettings().getLanguage() == Language::English) {
    	menuSubItemDeleteProfile->Caption = "Delete profile";
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
        menuSubItemDeleteProfile->Caption = "Obriši profil";
    }


    if (!menuSubItemSwitchUser) {
        menuSubItemSwitchUser = std::make_unique<TMenuItem>(MainMenu);
        menuSubItemSwitchUser->OnClick = MenuSubItemSwitchUserClick;
        menuItemProfile->Add(menuSubItemSwitchUser.get());
    }
    if (mainSession->getAppSettings().getLanguage() == Language::English) {
        menuSubItemSwitchUser->Caption = "Switch user";
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
        menuSubItemSwitchUser->Caption = "Promijeni korisnika";
    }

	if (authService->getUser().getUserType() == UserType::Guest) {

        menuItemProfile->Caption = "[guest]";

        if (menuSubItemViewProfile) {
            menuSubItemViewProfile->Visible	= false;
        }
        if (menuSubItemViewStatistics) {
            menuSubItemViewStatistics->Visible	= false;
        }
        if (menuSubItemDeleteProfile) {
            menuSubItemDeleteProfile->Visible	= false;
        }

    }
    else if (authService->getUser().getUserType() == UserType::Registered) {

        menuItemProfile->Caption = "[" + authService->getUser().getUsername() + "]";

    	if (menuSubItemViewProfile) {
            menuSubItemViewProfile->Visible	= true;
        }
        if (menuSubItemViewStatistics) {
            menuSubItemViewStatistics->Visible	= true;
        }
        if (menuSubItemDeleteProfile) {
            menuSubItemDeleteProfile->Visible = true;
        }
    }


}
