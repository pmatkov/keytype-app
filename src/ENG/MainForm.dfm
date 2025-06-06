object FMain: TFMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'KeyType'
  ClientHeight = 421
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu
  Position = poScreenCenter
  Scaled = False
  OnClose = FormClose
  TextHeight = 15
  object MainMenu: TMainMenu
    Left = 39
    Top = 339
    object MenuItemPractice: TMenuItem
      Caption = 'Practice'
      object MenuSubitemPracticeStart: TMenuItem
        Caption = 'Start'
        OnClick = MenuSubitemPracticeStartClick
      end
    end
    object MenuItemLessons: TMenuItem
      Caption = 'Lessons'
      object MenuSubItemLessonStart: TMenuItem
        Caption = 'Start'
        OnClick = MenuSubItemLessonStartClick
      end
      object MenuSubItemConfiguration: TMenuItem
        Caption = 'Configuration'
        OnClick = MenuSubItemConfigurationClick
      end
      object MenuSubItemLessonResults: TMenuItem
        Caption = 'Results'
        OnClick = MenuSubItemLessonResultsClick
      end
    end
    object MenuItemGames: TMenuItem
      Caption = 'Games'
      object MenuSubitemFlyingWords: TMenuItem
        Caption = 'Flying words'
        OnClick = MenuSubitemFlyingWordsClick
      end
    end
    object MenuItemSettings: TMenuItem
      Caption = 'Settings'
      object MenuSubitemPreferences: TMenuItem
        Caption = 'Preferences'
        OnClick = MenuSubitemPreferencesClick
      end
    end
    object MenuItemView: TMenuItem
      Caption = 'View'
      object MenuSubitemLogs: TMenuItem
        Caption = 'Logs'
        OnClick = MenuSubitemLogsClick
      end
    end
    object MenuItemHelp: TMenuItem
      Caption = 'Help'
      object MenuSubitemAbout: TMenuItem
        Caption = 'About'
        OnClick = MenuSubitemAboutClick
      end
    end
  end
end
