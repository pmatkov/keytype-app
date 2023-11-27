//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <memory>

#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("PracticeForm.cpp", FPractice);
USEFORM("OptionsFrame.cpp", FrOptions); /* TFrame: File Type */
USEFORM("MainForm.cpp", FMain);
USEFORM("LoginForm.cpp", FLogin);

#include "MainForm.h"
#include "PracticeForm.h"
#include "LoginForm.h"
#include "SessionModule.h"

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

		std::unique_ptr<SessionModule> sessionModule = std::make_unique<SessionModule>();

		std::unique_ptr<TFLogin> FLogin (new TFLogin(NULL));
		FLogin->setSessionModule(sessionModule.get());

		if (FLogin->ShowModal() == mrOk) {

			Application->CreateForm(__classid(TFMain), &FMain);
			Application->CreateForm(__classid(TFPractice), &FPractice);

			FMain->setSessionModule(sessionModule.get());
			FPractice->setSessionModule(sessionModule.get());

			Application->Run();
		}

	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
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
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
