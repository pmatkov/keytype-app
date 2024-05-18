//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <vcl.h>

#include <memory>
#include <vector>
#include <windows.h>

#include "MainSession.h"
#include "TypingSession.h"
#include "Parser.h"
#include "Logger.h"
#include "AuthenticationService.h"

#include "LessonsForm.h"
#include "LessonResultsForm.h"
#include "PreferencesForm.h"
#include "LogsForm.h"
#include "ProfileForm.h"
#include "AuthenticationForm.h"
#include "AchievementsForm.h"

#include "MainFrame.h"
#include "PracticeFrame.h"
#include "FlyingWordsFrame.h"
#include "Lessons2Frame.h"

#include "DataModule.h"

class UserStatistics;
class TFStatistics;
class TFAbout;
//---------------------------------------------------------------------------


class TFMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *MenuSubitemPracticeStart;
	TMenuItem *MenuItemSettings;
	TMenuItem *MenuSubitemPreferences;
	TMenuItem *MenuItemGames;
	TMenuItem *MenuSubitemFlyingWords;
	TMenuItem *MenuItemLessons;
	TMenuItem *MenuSubItemConfiguration;
	TMenuItem *MenuSubItemLessonStart;
	TMenuItem *MenuSubItemLessonResults;
	TMenuItem *MenuItemHelp;
	TMenuItem *MenuSubitemAbout;
	TMenuItem *MenuItemView;
	TMenuItem *MenuSubitemLogs;
	void __fastcall MenuSubitemPracticeStartClick(TObject *Sender);
	void __fastcall MenuSubitemPreferencesClick(TObject *Sender);
	void __fastcall MenuSubitemFlyingWordsClick(TObject *Sender);
	void __fastcall MenuSubItemConfigurationClick(TObject *Sender);
	void __fastcall MenuSubItemLessonStartClick(TObject *Sender);
    void __fastcall MenuSubItemViewProfileClick(TObject *Sender);
    void __fastcall MenuSubItemViewStatisticsClick(TObject *Sender);
    void __fastcall MenuSubItemViewAchievementsClick(TObject *Sender);
    void __fastcall MenuSubItemDeleteProfileClick(TObject *Sender);
    void __fastcall MenuSubItemSwitchUserClick(TObject *Sender);
	void __fastcall MenuSubItemLessonResultsClick(TObject *Sender);
	void __fastcall MenuSubitemAboutClick(TObject *Sender);
	void __fastcall MenuSubitemLogsClick(TObject *Sender);

private:	// User declarations

	std::unique_ptr<TFLessons> FLessons;
    std::unique_ptr<TFLessonResults> FLessonResults;
	std::unique_ptr<TFPreferences> FPreferences;
	std::unique_ptr<TFrMain> FrMain;
	std::unique_ptr<TFrPractice> FrPractice;
	std::unique_ptr<TFrFlyingWords> FrFlyingWords;
    std::unique_ptr<TFrLessons2> FrLessons2;
    std::unique_ptr<TFLogs> FLogs;
    std::unique_ptr<TFProfile> FProfile;
    std::unique_ptr<TFAchievements> FAchievements;

	TFStatistics *FStatistics;
	TFAbout *FAbout;
    UserStatistics *userStatistics;

	std::unique_ptr<MainSession> mainSession;
    std::unique_ptr<TypingSession> typingSession;
    std::unique_ptr<AuthenticationService> authService;
    std::unique_ptr<TFAuthentication> FAuthentication;

    std::unique_ptr<TMenuItem> menuItemProfile;
    std::unique_ptr<TMenuItem> menuSubItemViewProfile;
    std::unique_ptr<TMenuItem> menuSubItemViewStatistics;
    std::unique_ptr<TMenuItem> menuSubItemViewAchievements;
    std::unique_ptr<TMenuItem> menuSubItemDeleteProfile;
    std::unique_ptr<TMenuItem> menuSubItemSwitchUser;



    std::unique_ptr<Parser> parser;
    Logger &logger;

    TDataModule1 *dataModule;

public:		// User declarations

	__fastcall TFMain(TComponent* Owner);

    void setDataModule(TDataModule1 *_dataModule);

    void setMainSession(std::unique_ptr<MainSession> _mainSession);
    void setAuthenticationService(std::unique_ptr<AuthenticationService> _authService);
    void setAuthenticationForm(std::unique_ptr<TFAuthentication> _FAuthentication);

    void updateProfileMenu();

	virtual void __fastcall WndProc(TMessage &Message);

};


//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------

#endif
