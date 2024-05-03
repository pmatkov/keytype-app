object FMain: TFMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'KeyType'
  ClientHeight = 422
  ClientWidth = 628
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu
  Position = poScreenCenter
  Scaled = False
  TextHeight = 15
  object MainMenu: TMainMenu
    Left = 39
    Top = 339
    object MenuItemPractice: TMenuItem
      Caption = 'Practice'
      object MenuSubitemPracticeNew: TMenuItem
        Caption = 'New'
        OnClick = MenuSubitemPracticeNewClick
      end
    end
    object MenuItemLessons: TMenuItem
      Caption = 'Lessons'
      object MenuSubItemConfiguration: TMenuItem
        Caption = 'Configuration'
        OnClick = MenuSubItemConfigurationClick
      end
      object MenuSubItemLessonStart: TMenuItem
        Caption = 'Start'
        OnClick = MenuSubItemLessonStartClick
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
  end
end
