object FConverter: TFConverter
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Convert word list to JSON'
  ClientHeight = 122
  ClientWidth = 293
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnActivate = FormActivate
  TextHeight = 15
  object LInput: TLabel
    Left = 12
    Top = 32
    Width = 50
    Height = 15
    Caption = 'Input file:'
  end
  object LOutput: TLabel
    Left = 12
    Top = 70
    Width = 60
    Height = 15
    Caption = 'Output file:'
  end
  object LInfo: TLabel
    Left = 223
    Top = 101
    Width = 70
    Height = 15
    AutoSize = False
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
  end
  object BtConvert: TButton
    Left = 218
    Top = 66
    Width = 75
    Height = 25
    Caption = 'Convert'
    TabOrder = 0
    OnClick = BtConvertClick
  end
  object EInput: TEdit
    Left = 85
    Top = 29
    Width = 120
    Height = 23
    TabOrder = 1
  end
  object EOutput: TEdit
    Left = 85
    Top = 67
    Width = 120
    Height = 23
    Enabled = False
    TabOrder = 2
  end
  object BtBrowse: TButton
    Left = 218
    Top = 28
    Width = 75
    Height = 25
    Caption = 'Browse'
    TabOrder = 3
    OnClick = BtBrowseClick
  end
  object DFileOpen: TOpenTextFileDialog
    Left = 177
    Top = 65533
  end
  object msgDisplayTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = msgDisplayTimerTimer
    Left = 96
  end
end
