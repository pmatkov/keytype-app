//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <memory>

#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("PracticeFrame.cpp", FrPractice); /* TFrame: File Type */
USEFORM("RegisterFrame.cpp", FrRegister); /* TFrame: File Type */
USEFORM("PracticeForm.cpp", FPractice);
USEFORM("MainFrame.cpp", FrMain); /* TFrame: File Type */
USEFORM("OptionsFrame.cpp", FrOptions); /* TFrame: File Type */
USEFORM("MainForm.cpp", FMain);
USEFORM("DataModule.cpp", DataModule1); /* TDataModule: File Type */
USEFORM("AuthenticationForm.cpp", FAuthentication);
USEFORM("CustomTextFrame.cpp", FrCustomText); /* TFrame: File Type */
USEFORM("ExternalSourcesFrame.cpp", FrExternalSources); /* TFrame: File Type */
USEFORM("LoginFrame.cpp", FrLogin); /* TFrame: File Type */
USEFORM("GeneratedTextFrame.cpp", FrGeneratedText); /* TFrame: File Type */
USEFORM("PreferencesForm.cpp", FPreferences);
//---------------------------------------------------------------------------
#include "MainForm.h"
#include "PracticeForm.h"
#include "AuthenticationForm.h"
#include "Parser.h"
#include "Logger.h"
#include "StackTrace.h"
#include "MainSession.h"
#include "AuthenticationService.h"
#include "DataModule.h"

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

        // set up logging
        Logger::registerFlushOnExit();
        Logger::setLogLevel(LogLevel::All);

       	LOGGER(LogLevel::Info, "App started");

        // create main sessin and auth service
        std::unique_ptr<MainSession> mainSession = std::make_unique<MainSession>();
        std::unique_ptr<AuthenticationService> authService = std::make_unique<AuthenticationService>(mainSession.get());

        // create data module
        std::unique_ptr<TDataModule1> DataModule1 = std::make_unique<TDataModule1>(nullptr);
        // create authentication form
		std::unique_ptr<TFAuthentication> FAuthentication = std::make_unique<TFAuthentication>(nullptr, authService.get(), DataModule1.get());


		if (FAuthentication->ShowModal() == mrOk) {

            //  create main and options forms
			Application->CreateForm(__classid(TFMain), &FMain);
            std::unique_ptr<TFPreferences> FPreferences = std::make_unique<TFPreferences>(nullptr, mainSession.get());
            std::unique_ptr<TFPractice> FPractice = std::make_unique<TFPractice>(nullptr, mainSession.get());

            FMain->setPreferencesForm(FPreferences.get());
            FMain->setPracticeForm(FPractice.get());
            FMain->setMainSession(std::move(mainSession));

			Application->Run();
		}

	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
        LOGGER(LogLevel::Fatal, StackTrace::getStackTrace());
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
            LOGGER(LogLevel::Fatal, StackTrace::getStackTrace());
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
