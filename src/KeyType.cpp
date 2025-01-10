//---------------------------------------------------------------------------

#include <vcl.h>
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <memory>

#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("core\forms\converter\ConverterForm.cpp", FConverter);
USEFORM("core\forms\authentication\RegisterFrame.cpp", FrRegister); /* TFrame: File Type */
USEFORM("core\forms\authentication\LoginFrame.cpp", FrLogin); /* TFrame: File Type */
USEFORM("core\forms\authentication\AuthenticationForm.cpp", FAuthentication);
USEFORM("core\forms\logs\LogsForm.cpp", FLogs);
USEFORM("core\forms\lessons\LessonsFrame.cpp", FrLessons); /* TFrame: File Type */
USEFORM("core\forms\lessons\LessonResultsForm.cpp", FLessonResults);
USEFORM("core\forms\lessons\CoursesFrame.cpp", FrCourses); /* TFrame: File Type */
USEFORM("Core\dal\DataModule.cpp", DataModule1); /* TDataModule: File Type */
USEFORM("core\forms\practice\PracticeSourceForm.cpp", FPracticeSource);
USEFORM("core\forms\practice\OptionsFrame.cpp", FrOptions); /* TFrame: File Type */
USEFORM("core\forms\practice\KeyboardFrame.cpp", FrKeyboard); /* TFrame: File Type */
USEFORM("core\forms\practice\GeneratedTextFrame.cpp", FrGeneratedText); /* TFrame: File Type */
USEFORM("core\forms\practice\ExternalSourcesFrame.cpp", FrExternalSources); /* TFrame: File Type */
USEFORM("core\forms\profile\ProfileForm.cpp", FProfile);
USEFORM("core\forms\profile\AchievementsForm.cpp", FAchievements);
USEFORM("core\forms\preferences\PreferencesForm.cpp", FPreferences);
USEFORM("core\forms\main\MainFrame.cpp", FrMain); /* TFrame: File Type */
USEFORM("core\forms\main\MainForm.cpp", FMain);
USEFORM("core\forms\main\Lessons2Frame.cpp", FrLessons2); /* TFrame: File Type */
USEFORM("core\forms\main\FlyingWordsStatsFrame.cpp", FrFlyingWordsStats); /* TFrame: File Type */
USEFORM("core\forms\main\FlyingWordsFrame.cpp", FrFlyingWords); /* TFrame: File Type */
USEFORM("core\forms\practice\CustomTextFrame.cpp", FrCustomText); /* TFrame: File Type */
USEFORM("core\forms\main\TypingTextFrame.cpp", FrTypingText); /* TFrame: File Type */
USEFORM("core\forms\main\TypingStatsFrame.cpp", FrTypingStats); /* TFrame: File Type */
USEFORM("core\forms\main\PracticeFrame.cpp", FrPractice); /* TFrame: File Type */
USEFORM("Core\forms\lessons\LessonsForm.cpp", FLessons);
USEFORM("Core\forms\practice\PracticeForm.cpp", FPractice);
//---------------------------------------------------------------------------
#include "MainForm.h"
#include "PracticeSourceForm.h"
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

        LOGGER_SIMPLE("--App started--");

		std::unique_ptr<TDataModule1> DataModule1 = std::make_unique<TDataModule1>(nullptr);
		std::unique_ptr<AuthenticationService> authService = std::make_unique<AuthenticationService>(DataModule1.get());

        std::unique_ptr<TFAuthentication> FAuthentication = std::make_unique<TFAuthentication>(nullptr, authService.get());
		FAuthentication->Position = poScreenCenter;

		if (FAuthentication->ShowModal() == mrOk) {

			AppSettings appSettings(authService->getUser());
            TypingSettings typingSettings(authService->getUser());

            std::unique_ptr<MainSession> mainSession = std::make_unique<MainSession>(appSettings, typingSettings);

			//  main form
			Application->CreateForm(__classid(TFMain), &FMain);
		Application->CreateForm(__classid(TDataModule1), &DataModule1);
		Application->CreateForm(__classid(TFLessons), &FLessons);
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
