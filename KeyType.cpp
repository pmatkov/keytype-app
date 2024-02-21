//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <memory>

#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("PracticeFrame.cpp", FrPractice); /* TFrame: File Type */
USEFORM("OptionsFrame.cpp", FrOptions); /* TFrame: File Type */
USEFORM("PracticeForm.cpp", FPractice);
USEFORM("MainFrame.cpp", FrMain); /* TFrame: File Type */
USEFORM("ExternalSourcesFrame.cpp", FrExternalSources); /* TFrame: File Type */
USEFORM("CustomTextFrame.cpp", FrCustomText); /* TFrame: File Type */
USEFORM("LoginForm.cpp", FLogin);
USEFORM("MainForm.cpp", FMain);
USEFORM("GeneratedTextFrame.cpp", FrGeneratedText); /* TFrame: File Type */
//---------------------------------------------------------------------------
#include "MainForm.h"
#include "PracticeForm.h"
#include "LoginForm.h"
#include "Parser.h"
#include "Logger.h"
#include "StackTrace.h"
#include "MainSession.h"
#include "AuthenticationService.h"

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

        std::unique_ptr<MainSession> mainSession = std::make_unique<MainSession>();
        std::unique_ptr<AuthenticationService> authService = std::make_unique<AuthenticationService>(mainSession.get());

		std::unique_ptr<TFLogin> FLogin = std::make_unique<TFLogin>(nullptr, authService.get());

		if (FLogin->ShowModal() == mrOk) {

			Application->CreateForm(__classid(TFMain), &FMain);
            std::unique_ptr<TFPractice> FPractice = std::make_unique<TFPractice>(nullptr, mainSession.get());

            FMain->setMainSession(std::move(mainSession));
            FMain->setPracticeForm(FPractice.get());

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
