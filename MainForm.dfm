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
  TextHeight = 15
  object MainMenu: TMainMenu
    Left = 33
    Top = 354
    object MenuItemPractice: TMenuItem
      Caption = 'Practice'
      object MenuSubitemPracticeNew: TMenuItem
        Caption = 'New'
        OnClick = MenuSubitemPracticeNewClick
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
