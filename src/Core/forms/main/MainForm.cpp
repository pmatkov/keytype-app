//---------------------------------------------------------------------------
#undef UNICODE
#define UNICODE

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"

#include <System.DateUtils.hpp>

#include "UIUtils.h"
#include "TextUtils.h"
#include "EnumUtils.h"
#include "FileUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"

#include "GameThread.h"
#include "KeyStatistics.h"
#include "Lib\\Statistics\\UserStatistics.h"
#include "Lib\\Statistics\\StatisticsForm.h"
#include "Lib\\About\\AboutForm.h"

//---------------------------------------------------------------------------
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

        // set font, language and logo

		UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());
        UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());

        FrMain->setLogo();

    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFMain::setAuthenticationService(std::unique_ptr<AuthenticationService> _authService) {

    if (_authService) {
      	authService = std::move(_authService);

        updateProfileMenu();
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFMain::setAuthenticationForm(std::unique_ptr<TFAuthentication> _FAuthentication) {

    if (_FAuthentication) {
      	FAuthentication = std::move(_FAuthentication);

    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

// dispatch char messages to active frame

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

// menu practice/ start

void __fastcall TFMain::MenuSubitemPracticeStartClick(TObject *Sender)
{

	if (!typingSession) {
       typingSession = std::make_unique<TypingSession>();
    }

    if (!parser) {
		parser = std::make_unique<Parser>(mainSession.get(), typingSession.get());
    }

	if (FrPractice) {
		FrPractice.reset();
	}

	if (!FrPractice) {
		FrPractice = UIUtils::createFrame<TFrPractice>(this, parser.get(), mainSession.get(), typingSession.get(), dataModule, authService.get());

		//  set subclass procedure for REText
		SetWindowSubclass(FrPractice->FrTypingText->REText->Handle, &FrPractice->FrTypingText->RESubclass, 0, 0);
	}

    typingSession->setSessionType(SessionType::Practice);

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

// menu lessons/ start

void __fastcall TFMain::MenuSubItemLessonStartClick(TObject *Sender)
{
  	if (!typingSession) {
       typingSession = std::make_unique<TypingSession>();
    }
    if (!parser) {
        parser = std::make_unique<Parser>(mainSession.get(), typingSession.get());
	}

	if (FrLessons2) {
		FrLessons2.reset();
	}
	if (!FrLessons2) {

		FrLessons2 = UIUtils::createFrame<TFrLessons2>(this, parser.get(), mainSession.get(), typingSession.get(), authService.get(), dataModule);

        //  set subclass procedure for REText
		SetWindowSubclass(FrLessons2->FrTypingText->REText->Handle, &FrLessons2->FrTypingText->RESubclass, 0, 0);
	}

    typingSession->setSessionType(SessionType::Lesson);

	if (FrMain && FrMain->Visible) {
		UIUtils::switchFrames<TFrMain, TFrLessons2>(FrMain, FrLessons2);
	}

    else if (FrPractice && FrPractice->Visible) {
		UIUtils::switchFrames<TFrPractice, TFrLessons2>(FrPractice, FrLessons2);
	}

    // terminate thread and cleanup
	else if (FrFlyingWords && FrFlyingWords->Visible) {

    	FrFlyingWords->getGameEngine().threadTerminate();
        FrFlyingWords->getGameEngine().gameCleanup();
		UIUtils::switchFrames<TFrFlyingWords, TFrLessons2>(FrFlyingWords, FrLessons2);
	}
}

// menu lessons/ configuration

void __fastcall TFMain::MenuSubItemConfigurationClick(TObject *Sender)
{
	if (FLessons) {
		FLessons.reset();
	}
	if (!FLessons) {
		FLessons = std::make_unique<TFLessons>(nullptr, dataModule);
        FLessons->Position = poMainFormCenter;
	}

 	FLessons->ShowModal();
}

// menu lessons/ results

void __fastcall TFMain::MenuSubItemLessonResultsClick(TObject *Sender)
{
	if (FLessonResults) {
		FLessonResults.reset();
	}
	if (!FLessonResults) {
		FLessonResults = std::make_unique<TFLessonResults>(nullptr, dataModule);
        FLessonResults->Position = poMainFormCenter;
	}

    FLessonResults->ShowModal();
}

// menu games/ flying words

void __fastcall TFMain::MenuSubitemFlyingWordsClick(TObject *Sender)
{

	if (FrFlyingWords) {
		FrFlyingWords.reset();
	}
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

// menu settings/ preferences

void __fastcall TFMain::MenuSubitemPreferencesClick(TObject *Sender)
{
	if (FPreferences) {
		FPreferences.reset();
	}
	if (!FPreferences) {
		FPreferences = std::make_unique<TFPreferences>(nullptr, mainSession.get(), authService.get());
		FPreferences->Position = poMainFormCenter;
	}

    if (FPreferences->ShowModal() == mrOk) {

        // change language

        if (mainSession->getAppSettings().getLanguageChanged()) {
            UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());
            mainSession->getAppSettings().setLanguageChanged(false);
        }
        if (FrPractice && FrPractice->Visible) {
            FrPractice.reset();
        	FrPractice = UIUtils::createFrame<TFrPractice>(this, parser.get(), mainSession.get(), typingSession.get(), dataModule, authService.get());

            //  set subclass procedure for REText
            SetWindowSubclass(FrPractice->FrTypingText->REText->Handle, &FrPractice->FrTypingText->RESubclass, 0, 0);
        }
    }
}

// menu view/ logs

void __fastcall TFMain::MenuSubitemLogsClick(TObject *Sender)
{

	if (FLogs) {
		FLogs.reset();
	}
	if (!FLogs) {
		FLogs = std::make_unique<TFLogs>(nullptr, authService.get(), dataModule);
        FLogs->Position = poMainFormCenter;
	}

 	FLogs->ShowModal();
}

// menu profile/ view profile

void __fastcall TFMain::MenuSubItemViewProfileClick(TObject *Sender) {

	if (FProfile) {
		FProfile.reset();
	}
	if (!FProfile) {
		FProfile = std::make_unique<TFProfile>(nullptr, mainSession.get(), authService.get(), dataModule);
	}

    FProfile->Position = poMainFormCenter;
    FProfile->ShowModal();
}

// menu profile/ view statistics

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

        // load StatisticsLib.dll

    	HINSTANCE Statistics;

        if ((Statistics = LoadLibrary(L"StatisticsLib.dll")) == nullptr) {
        	LOGGER(LogLevel::Debug, "Failed to load dll");
            ShowMessage("Failed to load dll");
            return;
        }

        typedef UserStatistics*(*__stdcall pCreateUserStatistics)(const std::vector<TDateTime>&, const std::map<wchar_t, KeyStatistics>&);
        pCreateUserStatistics CreateUserStatistics;

        if ((CreateUserStatistics = (pCreateUserStatistics)GetProcAddress(Statistics, "CreateUserStatistics")) == nullptr) {
          	LOGGER(LogLevel::Debug, "Can't find CreateUserStatistics function in dll");
            ShowMessage("Can't find CreateUserStatistics function in dll");
			return;
        }

    	userStatistics = CreateUserStatistics(practiceTime, keyStatistics);

		typedef void(*__stdcall pCreateStatisticsForm)(UserStatistics *userStatistics);
        pCreateStatisticsForm CreateStatisticsForm;

        if ((CreateStatisticsForm = (pCreateStatisticsForm)GetProcAddress(Statistics, "CreateStatisticsForm")) == nullptr) {
        	LOGGER(LogLevel::Debug, "Can't find CreateStatisticsForm function in dll");
            ShowMessage("Can't find CreateStatisticsForm function in dll");
            return;
        }

		CreateStatisticsForm(userStatistics);
		FreeLibrary(Statistics);
	}
}

// menu profile/ view achievements

void __fastcall TFMain::MenuSubItemViewAchievementsClick(TObject *Sender) {


	if (FAchievements) {
		FAchievements.reset();
	}

	if (!FAchievements) {
		FAchievements = std::make_unique<TFAchievements>(nullptr, authService.get(), dataModule);
		FAchievements->Position = poMainFormCenter;
	}

    FAchievements->ShowModal();
}

// menu profile/ delete profile

void __fastcall TFMain::MenuSubItemDeleteProfileClick(TObject *Sender) {

	if (dataModule->TUsers->Locate("username", authService->getUser().getUsername(), TLocateOptions())) {

		dataModule->TUsers->Delete();
    }
    authService->loginUser("guest", "");
    updateProfileMenu();

}

// menu profile/ switch user

void __fastcall TFMain::MenuSubItemSwitchUserClick(TObject *Sender) {

	if (FAuthentication) {
		FAuthentication.reset();
	}

	if (!FAuthentication) {

       FAuthentication = std::make_unique<TFAuthentication>(nullptr, authService.get());
	}
    FAuthentication->Position = poMainFormCenter;

    // change font and language

    if (FAuthentication->ShowModal() == mrOk) {

        if (authService->getUserChanged()) {

        	UnicodeString previousFontFamily =  mainSession->getAppSettings().getFontFamily();
            Language previousLanguage = mainSession->getAppSettings().getLanguage();

            AppSettings appSettings(authService->getUser());
            TypingSettings typingSettings(authService->getUser());

            mainSession->setAppSettings(appSettings);
            mainSession->setTypingSettings(typingSettings);

            if (previousFontFamily != mainSession->getAppSettings().getFontFamily()) {
            	UIUtils::changeFontFamily(this, mainSession->getAppSettings().getFontFamily());
            }
            if (previousLanguage != mainSession->getAppSettings().getLanguage()) {
            	UIUtils::changeLanguage(mainSession->getAppSettings().getLanguage());
            }

            authService->setUserChanged(false);
        }

        updateProfileMenu();
    }
}

// menu help/ about

void __fastcall TFMain::MenuSubitemAboutClick(TObject *Sender)
{
	if (!FAbout) {

      	HINSTANCE About;

        if ((About = LoadLibrary(L"AboutLib.dll")) == nullptr) {
        	LOGGER(LogLevel::Debug, "Failed to load dll");
            ShowMessage("Failed to load dll");
            return;
        }

		typedef void(*__stdcall pCreateAboutForm)();
        pCreateAboutForm CreateAboutForm;

        if ((CreateAboutForm = (pCreateAboutForm)GetProcAddress(About, "CreateAboutForm")) == nullptr) {
        	LOGGER(LogLevel::Debug, "Can't find CreateAboutForm function in dll");
            ShowMessage("Can't find CreateAboutForm function in dll");
            return;
        }

   		CreateAboutForm();
		FreeLibrary(About);
    }
}


// dynamically update profile menu based on logged in user

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

    if (TFile::Exists(projectExePath + "StatisticsLib.dll")) {

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

    if (!menuSubItemViewAchievements) {
        menuSubItemViewAchievements = std::make_unique<TMenuItem>(MainMenu);
        menuSubItemViewAchievements->OnClick = MenuSubItemViewAchievementsClick;
        menuItemProfile->Add(menuSubItemViewAchievements.get());
    }
    if (mainSession->getAppSettings().getLanguage() == Language::English) {
        menuSubItemViewAchievements->Caption = "View achievements";
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
        menuSubItemViewAchievements->Caption = "Pregledaj postignuca";
    }

    if (!menuSubItemProfileSeparator) {
    	menuSubItemProfileSeparator = std::make_unique<TMenuItem>(MainMenu);
        menuSubItemProfileSeparator->Caption = "-";
    	menuItemProfile->Add(menuSubItemProfileSeparator.get());
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

	if (authService->getUser().getUserType() == UserType::Guest) {

        menuItemProfile->Caption = "[guest]";

        if (menuSubItemViewProfile) {
            menuSubItemViewProfile->Visible	= false;
        }
        if (menuSubItemDeleteProfile) {
            menuSubItemDeleteProfile->Visible = false;
        }
        if (menuSubItemViewStatistics) {
            menuSubItemViewStatistics->Visible = false;
        }
        if (menuSubItemProfileSeparator) {
            menuSubItemProfileSeparator->Visible = false;
        }
        if (menuSubItemViewAchievements) {
            menuSubItemViewAchievements->Visible = false;
		}
    }

    // display additional menu subitems for registered user

    else if (authService->getUser().getUserType() == UserType::Registered) {

        menuItemProfile->Caption = "[" + authService->getUser().getUsername() + "]";

    	if (menuSubItemViewProfile) {
            menuSubItemViewProfile->Visible	= true;
        }
        if (menuSubItemDeleteProfile) {
            menuSubItemDeleteProfile->Visible = true;
        }
        if (menuSubItemViewStatistics) {
            menuSubItemViewStatistics->Visible = true;
        }
        if (menuSubItemProfileSeparator) {
            menuSubItemProfileSeparator->Visible = true;
        }
        if (menuSubItemViewAchievements) {
            menuSubItemViewAchievements->Visible = true;
		}
    }
}

