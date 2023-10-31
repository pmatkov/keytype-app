object FMain: TFMain
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'KeyType'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  TextHeight = 15
  object Label1: TLabel
    Left = 153
    Top = 328
    Width = 3
    Height = 15
    WordWrap = True
  end
  object StartInfo: TLabel
    Left = 216
    Top = 280
    Width = 185
    Height = 15
    Caption = 'Press space bar to start the practice'
    OnClick = StartInfoClick
  end
  object TextBox: TRichEdit
    Left = 216
    Top = 144
    Width = 185
    Height = 89
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
end
