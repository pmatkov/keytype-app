object FMain: TFMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'KeyType'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  TextHeight = 15
  object StartLabel: TLabel
    Left = 216
    Top = 232
    Width = 187
    Height = 17
    Caption = 'Press space to start the practice'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object TextBox: TRichEdit
    Left = 128
    Top = 144
    Width = 360
    Height = 65
    BorderStyle = bsNone
    Color = clBtnFace
    Enabled = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Transparent = True
  end
  inline Frame11: TFrame1
    Left = 505
    Top = 144
    Width = 111
    Height = 168
    TabOrder = 1
    ExplicitLeft = 505
    ExplicitTop = 144
  end
end
