//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <memory>

#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("PracticeOptionsForm.cpp", FPractice);
USEFORM("PreferencesForm.cpp", FPreferences);
USEFORM("RegisterFrame.cpp", FrRegister); /* TFrame: File Type */
USEFORM("PracticeFrame.cpp", FrPractice); /* TFrame: File Type */
USEFORM("MainForm.cpp", FMain);
USEFORM("MainFrame.cpp", FrMain); /* TFrame: File Type */
USEFORM("OptionsFrame.cpp", FrOptions); /* TFrame: File Type */
USEFORM("DataModule.cpp", DataModule1); /* TDataModule: File Type */
USEFORM("AuthenticationForm.cpp", FAuthentication);
USEFORM("CustomTextFrame.cpp", FrCustomText); /* TFrame: File Type */
USEFORM("LoginFrame.cpp", FrLogin); /* TFrame: File Type */
USEFORM("ExternalSourcesFrame.cpp", FrExternalSources); /* TFrame: File Type */
USEFORM("GeneratedTextFrame.cpp", FrGeneratedText); /* TFrame: File Type */
//---------------------------------------------------------------------------
#include "MainForm.h"
#include "PracticeOptionsForm.h"
#include "AuthenticationForm.h"
#include "Parser.h"
#include "Logger.h"
#include "StackTrace.h"
#include "MainSession.h"
#include "AuthenticationService.h"
#include "DataModule.h"
#include "ENullPointerException.h"

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

        // set up logging
       	LOGGER(LogLevel::Info, "App started");

        std::unique_ptr<TDataModule1> DataModule1 = std::make_unique<TDataModule1>(nullptr);
        std::unique_ptr<AuthenticationService> authService = std::make_unique<AuthenticationService>(DataModule1.get());

        // create auth form
        std::unique_ptr<TFAuthentication> FAuthentication = std::make_unique<TFAuthentication>(nullptr, authService.get());
        FAuthentication->Position = poScreenCenter;

		if (FAuthentication->ShowModal() == mrOk) {

        	User user = authService->getUser();
            AppSettings appSettings(user);
            TypingSettings typingSettings(user);

            std::unique_ptr<MainSession> mainSession = std::make_unique<MainSession>(appSettings, typingSettings);

            //  create main form, options form and preferences forms
			Application->CreateForm(__classid(TFMain), &FMain);
			FMain->Position = poScreenCenter;

			std::unique_ptr<TFPreferences> FPreferences = std::make_unique<TFPreferences>(nullptr, mainSession.get(), authService.get());
            FPreferences->Position = poMainFormCenter;

            std::unique_ptr<TFPracticeOptions> FPracticeOptions = std::make_unique<TFPracticeOptions>(nullptr, mainSession.get());
            FPracticeOptions->Position = poMainFormCenter;

            FMain->setPreferencesForm(FPreferences.get());
            FMain->setPracticeOptionsForm(FPracticeOptions.get());
            FMain->setMainSession(std::move(mainSession));
            FMain->setAuthenticationService(std::move(authService));

			Application->Run();
		}

	}
	catch (Exception &ex)
	{
		Application->ShowException(&ex);
        LOGGER(LogLevel::Fatal, ex.Message);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &ex)
		{
			Application->ShowException(&ex);
            LOGGER(LogLevel::Fatal, ex.Message);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
