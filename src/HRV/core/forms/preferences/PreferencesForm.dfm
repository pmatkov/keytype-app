object FPreferences: TFPreferences
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Preferences'
  ClientHeight = 467
  ClientWidth = 527
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  TextHeight = 15
  object GroupBox1: TGroupBox
    Left = 6
    Top = 27
    Width = 254
    Height = 391
    Caption = 'Application settings'
    TabOrder = 0
    object LLanguage: TLabel
      Left = 12
      Top = 37
      Width = 55
      Height = 15
      Caption = 'Language:'
    end
    object LLogging: TLabel
      Left = 12
      Top = 149
      Width = 47
      Height = 15
      Caption = 'Logging:'
    end
    object LFont1: TLabel
      Left = 12
      Top = 73
      Width = 63
      Height = 15
      Caption = 'Font family:'
    end
    object LArchiveLogLimit: TLabel
      Left = 12
      Top = 186
      Width = 70
      Height = 15
      Caption = 'Archive limit:'
    end
    object LArchiveStatus: TLabel
      Left = 12
      Top = 224
      Width = 140
      Height = 15
      AutoSize = False
    end
    object CBLanguage: TComboBox
      Left = 126
      Top = 34
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 0
      OnChange = CBLanguageChange
    end
    object CBLogLevel: TComboBox
      Left = 126
      Top = 146
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 1
      OnChange = CBLogLevelChange
    end
    object CBLoggingEnable: TCheckBox
      Left = 93
      Top = 149
      Width = 16
      Height = 17
      TabOrder = 2
      OnClick = CBLoggingEnableClick
    end
    object CBFont1: TComboBox
      Left = 126
      Top = 70
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 3
      OnChange = CBFont1Change
    end
    object BtReset1: TButton
      Left = 151
      Top = 348
      Width = 90
      Height = 25
      Caption = 'Reset'
      TabOrder = 4
      OnClick = BtReset1Click
    end
    object CBArchiveLogLimit: TComboBox
      Left = 126
      Top = 183
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 5
      OnChange = CBArchiveLogLimitChange
    end
    object BtArchiveLogs: TButton
      Left = 151
      Top = 224
      Width = 90
      Height = 25
      Cancel = True
      Caption = 'Archive logs'
      TabOrder = 6
      OnClick = BtArchiveLogsClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 266
    Top = 27
    Width = 254
    Height = 391
    Caption = 'Typing settings'
    TabOrder = 1
    object LCaret: TLabel
      Left = 12
      Top = 37
      Width = 57
      Height = 15
      Caption = 'Caret type:'
    end
    object LFont2: TLabel
      Left = 12
      Top = 109
      Width = 63
      Height = 15
      Caption = 'Font family:'
    end
    object LFontSize: TLabel
      Left = 12
      Top = 149
      Width = 49
      Height = 15
      Caption = 'Font size:'
    end
    object LSeparator: TLabel
      Left = 12
      Top = 73
      Width = 79
      Height = 15
      Caption = 'Separator type:'
    end
    object LKeyboardLayout: TLabel
      Left = 13
      Top = 186
      Width = 89
      Height = 15
      Caption = 'Keyboard layout:'
    end
    object CBCaret: TComboBox
      Left = 126
      Top = 34
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 0
      OnChange = CBCaretChange
    end
    object CBMistake: TCheckBox
      Left = 12
      Top = 222
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Stop on mistake:'
      TabOrder = 1
      OnClick = CBMistakeClick
    end
    object CBConsecutiveMistakes: TCheckBox
      Left = 12
      Top = 254
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Count consecutive mistakes:'
      TabOrder = 2
      OnClick = CBConsecutiveMistakesClick
    end
    object CBSpeed: TCheckBox
      Left = 12
      Top = 284
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Display speed:'
      TabOrder = 3
      OnClick = CBSpeedClick
    end
    object CBFont2: TComboBox
      Left = 126
      Top = 106
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 4
      OnChange = CBFont2Change
    end
    object CBAccuracy: TCheckBox
      Left = 12
      Top = 317
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Display accuracy:'
      TabOrder = 5
      OnClick = CBAccuracyClick
    end
    object CBFontSize: TComboBox
      Left = 126
      Top = 146
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 6
      OnChange = CBFontSizeChange
    end
    object BtReset2: TButton
      Left = 147
      Top = 348
      Width = 90
      Height = 25
      Caption = 'Reset'
      TabOrder = 7
      OnClick = BtReset2Click
    end
    object CBSeparator: TComboBox
      Left = 126
      Top = 70
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 8
      OnChange = CBSeparatorChange
    end
    object CBKeyboardLayout: TComboBox
      Left = 127
      Top = 183
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 9
      OnChange = CBKeyboardLayoutChange
    end
  end
  object BtCancel: TButton
    Left = 444
    Top = 435
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object BtAccept: TButton
    Left = 349
    Top = 435
    Width = 75
    Height = 25
    Caption = 'Accept'
    ModalResult = 1
    TabOrder = 3
    OnClick = BtAcceptClick
  end
  object msgDisplayTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = msgDisplayTimerTimer
    Left = 69
    Top = 312
  end
end
