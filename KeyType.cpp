//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <memory>

#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("LoginFrame.cpp", FrLogin); /* TFrame: File Type */
USEFORM("LessonsFrame.cpp", FrLessons); /* TFrame: File Type */
USEFORM("MainForm.cpp", FMain);
USEFORM("MainFrame.cpp", FrMain); /* TFrame: File Type */
USEFORM("LessonsForm.cpp", FLessons);
USEFORM("Lessons2Frame.cpp", FrLessons2); /* TFrame: File Type */
USEFORM("LessonResultsForm.cpp", FLessonResults);
USEFORM("PracticeFrame.cpp", FrPractice); /* TFrame: File Type */
USEFORM("TypingTextFrame.cpp", FrTypingText); /* TFrame: File Type */
USEFORM("TypingStatsFrame.cpp", FrTypingStats); /* TFrame: File Type */
USEFORM("ProfileForm.cpp", FProfile);
USEFORM("PreferencesForm.cpp", FPreferences);
USEFORM("PracticeOptionsForm.cpp", FPractice);
USEFORM("RegisterFrame.cpp", FrRegister); /* TFrame: File Type */
USEFORM("CustomTextFrame.cpp", FrCustomText); /* TFrame: File Type */
USEFORM("CoursesFrame.cpp", FrCourses); /* TFrame: File Type */
USEFORM("ConverterForm.cpp", FConverter);
USEFORM("DataModule.cpp", DataModule1); /* TDataModule: File Type */
USEFORM("AchievementsForm.cpp", FAchievements);
USEFORM("AuthenticationForm.cpp", FAuthentication);
USEFORM("GeneratedTextFrame.cpp", FrGeneratedText); /* TFrame: File Type */
USEFORM("ExternalSourcesFrame.cpp", FrExternalSources); /* TFrame: File Type */
USEFORM("FlyingWordsStatsFrame.cpp", FrFlyingWordsStats); /* TFrame: File Type */
USEFORM("FlyingWordsFrame.cpp", FrFlyingWords); /* TFrame: File Type */
USEFORM("LogsForm.cpp", FLogs);
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
#include "Dictionary.h"

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

        LOGGER_SIMPLE("--Main app started--");

		std::unique_ptr<TDataModule1> DataModule1 = std::make_unique<TDataModule1>(nullptr);
		std::unique_ptr<AuthenticationService> authService = std::make_unique<AuthenticationService>(DataModule1.get());

        std::unique_ptr<TFAuthentication> FAuthentication = std::make_unique<TFAuthentication>(nullptr, authService.get());
		FAuthentication->Position = poScreenCenter;

		if (FAuthentication->ShowModal() == mrOk) {

			AppSettings appSettings(authService->getUser());
            TypingSettings typingSettings(authService->getUser());

            std::unique_ptr<MainSession> mainSession = std::make_unique<MainSession>(appSettings, typingSettings);

			//  create main form
			Application->CreateForm(__classid(TFMain), &FMain);
            Application->CreateForm(__classid(TFAchievements), &FAchievements);
            Application->CreateForm(__classid(TFLogs), &FLogs);
            FMain->Position = poScreenCenter;

            FMain->setMainSession(std::move(mainSession));
            FMain->setDataModule(DataModule1.get());
            FMain->setAuthenticationService(std::move(authService));
            FMain->setAuthenticationForm(std::move(FAuthentication));

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
    Logger &logger = Logger::getLogger();
    logger.writeToFile();

	return 0;
}
//---------------------------------------------------------------------------
