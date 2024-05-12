//---------------------------------------------------------------------------
#include <vcl.h>
#include <tchar.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("ServerForm.cpp", FServer);
USEFORM("DataModule.cpp", DataModule2); /* TDataModule: File Type */
//---------------------------------------------------------------------------
#include "ServerForm.h"
#include "DataModule.h"
#include "Logger.h"

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
    	LOGGER_SIMPLE("--Server started--");

		Application->Initialize();
		Application->MainFormOnTaskBar = true;

		std::unique_ptr<TDataModule2> DataModule2 = std::make_unique<TDataModule2>(nullptr);

		Application->CreateForm(__classid(TFServer), &FServer);
		FServer->Position = poScreenCenter;
		FServer->setDataModule(DataModule2.get());

		Application->Run();
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

    Logger &logger = Logger::getLogger();
    logger.writeToFile();

	return 0;
}
//---------------------------------------------------------------------------
