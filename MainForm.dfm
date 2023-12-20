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
  end
end
