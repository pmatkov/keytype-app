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
      Caption = 'Vje'#382'ba'
      object MenuSubitemPracticeStart: TMenuItem
        Caption = 'Pokreni'
        OnClick = MenuSubitemPracticeStartClick
      end
    end
    object MenuItemLessons: TMenuItem
      Caption = 'Lekcije'
      object MenuSubItemLessonStart: TMenuItem
        Caption = 'Pokreni'
        OnClick = MenuSubItemLessonStartClick
      end
      object MenuSubItemConfiguration: TMenuItem
        Caption = 'Konfiguracija'
        OnClick = MenuSubItemConfigurationClick
      end
      object MenuSubItemLessonResults: TMenuItem
        Caption = 'Rezultati'
        OnClick = MenuSubItemLessonResultsClick
      end
    end
    object MenuItemGames: TMenuItem
      Caption = 'Igre'
      object MenuSubitemFlyingWords: TMenuItem
        Caption = 'Lete'#263'e rije'#269'i'
        OnClick = MenuSubitemFlyingWordsClick
      end
    end
    object MenuItemSettings: TMenuItem
      Caption = 'Postavke'
      object MenuSubitemPreferences: TMenuItem
        Caption = 'Preferencije'
        OnClick = MenuSubitemPreferencesClick
      end
    end
    object MenuItemView: TMenuItem
      Caption = 'Pregledaj'
      object MenuSubitemLogs: TMenuItem
        Caption = 'Logove'
        OnClick = MenuSubitemLogsClick
      end
    end
    object MenuItemHelp: TMenuItem
      Caption = 'Pomo'#263
      object MenuSubitemAbout: TMenuItem
        Caption = 'O aplikaciji'
        OnClick = MenuSubitemAboutClick
      end
    end
  end
end
