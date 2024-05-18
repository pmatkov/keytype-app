object FAbout: TFAbout
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'About KeyType'
  ClientHeight = 202
  ClientWidth = 308
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object LVersion: TLabel
    Left = 45
    Top = 33
    Width = 76
    Height = 15
    Caption = 'Keytype v 0.1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LCreated: TLabel
    Left = 45
    Top = 57
    Width = 129
    Height = 15
    Caption = 'Created on May 11, 2024'
  end
  object BtOk: TButton
    Left = 210
    Top = 156
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
  end
end
