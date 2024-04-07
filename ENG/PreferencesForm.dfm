object FPreferences: TFPreferences
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Preferences'
  ClientHeight = 444
  ClientWidth = 534
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  TextHeight = 15
  object GroupBox1: TGroupBox
    Left = 8
    Top = 27
    Width = 254
    Height = 370
    Caption = 'Application settings'
    TabOrder = 0
    object LLanguage: TLabel
      Left = 12
      Top = 45
      Width = 55
      Height = 15
      Caption = 'Language:'
    end
    object LLogging: TLabel
      Left = 12
      Top = 157
      Width = 47
      Height = 15
      Caption = 'Logging:'
    end
    object LFont1: TLabel
      Left = 12
      Top = 81
      Width = 63
      Height = 15
      Caption = 'Font family:'
    end
    object LArchiveLogs: TLabel
      Left = 12
      Top = 194
      Width = 68
      Height = 15
      Caption = 'Archive logs:'
    end
    object CBLanguage: TComboBox
      Left = 126
      Top = 42
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 0
      OnChange = CBLanguageChange
    end
    object CBLogging: TComboBox
      Left = 126
      Top = 154
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 1
      OnChange = CBLoggingChange
    end
    object CBLoggingEnable: TCheckBox
      Left = 93
      Top = 157
      Width = 16
      Height = 17
      TabOrder = 2
      OnClick = CBLoggingEnableClick
    end
    object CBFont1: TComboBox
      Left = 126
      Top = 78
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 3
      OnChange = CBFont1Change
    end
    object BtReset1: TButton
      Left = 166
      Top = 330
      Width = 75
      Height = 25
      Caption = 'Reset'
      TabOrder = 4
      OnClick = BtReset1Click
    end
    object CBLogInterval: TComboBox
      Left = 126
      Top = 191
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 5
      OnChange = CBLogIntervalChange
    end
  end
  object GroupBox2: TGroupBox
    Left = 276
    Top = 27
    Width = 254
    Height = 370
    Caption = 'Typing settings'
    TabOrder = 1
    object LCaret: TLabel
      Left = 12
      Top = 45
      Width = 57
      Height = 15
      Caption = 'Caret type:'
    end
    object LFont2: TLabel
      Left = 12
      Top = 117
      Width = 63
      Height = 15
      Caption = 'Font family:'
    end
    object LFontSize: TLabel
      Left = 12
      Top = 157
      Width = 49
      Height = 15
      Caption = 'Font size:'
    end
    object LSeparator: TLabel
      Left = 12
      Top = 81
      Width = 79
      Height = 15
      Caption = 'Separator type:'
    end
    object CBCaret: TComboBox
      Left = 126
      Top = 42
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 0
      OnChange = CBCaretChange
    end
    object CBMistake: TCheckBox
      Left = 12
      Top = 195
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Stop on mistake:'
      TabOrder = 1
      OnClick = CBMistakeClick
    end
    object CBConsecutiveMistakes: TCheckBox
      Left = 12
      Top = 228
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Count consecutive mistakes:'
      TabOrder = 2
      OnClick = CBConsecutiveMistakesClick
    end
    object CBSpeed: TCheckBox
      Left = 12
      Top = 261
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Display speed:'
      TabOrder = 3
      OnClick = CBSpeedClick
    end
    object CBFont2: TComboBox
      Left = 126
      Top = 114
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 4
      OnChange = CBFont2Change
    end
    object CBAccuracy: TCheckBox
      Left = 12
      Top = 294
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Display accuracy:'
      TabOrder = 5
      OnClick = CBAccuracyClick
    end
    object CBFontSize: TComboBox
      Left = 126
      Top = 154
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 6
      OnChange = CBFontSizeChange
    end
    object BtReset2: TButton
      Left = 162
      Top = 330
      Width = 75
      Height = 25
      Caption = 'Reset'
      TabOrder = 7
      OnClick = BtReset2Click
    end
    object CBSeparator: TComboBox
      Left = 126
      Top = 78
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 8
      OnChange = CBSeparatorChange
    end
  end
  object BtCancel: TButton
    Left = 449
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object BtAccept: TButton
    Left = 352
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Accept'
    ModalResult = 1
    TabOrder = 3
    OnClick = BtAcceptClick
  end
end
