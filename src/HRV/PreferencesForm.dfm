object FPreferences: TFPreferences
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Postavke'
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
    Caption = 'Postavke aplikacije'
    TabOrder = 0
    object LLanguage: TLabel
      Left = 12
      Top = 37
      Width = 55
      Height = 15
      Caption = 'Jezik:'
    end
    object LLogging: TLabel
      Left = 12
      Top = 149
      Width = 47
      Height = 15
      Caption = 'Bilje'#382'enje:'
    end
    object LFont1: TLabel
      Left = 12
      Top = 73
      Width = 63
      Height = 15
      Caption = 'Vrsta fonta:'
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
    object CBLogging: TComboBox
      Left = 126
      Top = 146
      Width = 115
      Height = 23
      Style = csDropDownList
      TabOrder = 1
      OnChange = CBLoggingChange
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
      Caption = 'Resetiraj'
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
      Caption = 'Arhiv. zapise'
      TabOrder = 6
      OnClick = BtArchiveLogsClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 266
    Top = 27
    Width = 254
    Height = 391
    Caption = 'Postavke tipkanja'
    TabOrder = 1
    object LCaret: TLabel
      Left = 12
      Top = 37
      Width = 57
      Height = 15
      Caption = 'Vrsta pokaziva'#269'a:'
    end
    object LFont2: TLabel
      Left = 12
      Top = 109
      Width = 63
      Height = 15
      Caption = 'Vrsta fonta:'
    end
    object LFontSize: TLabel
      Left = 12
      Top = 149
      Width = 49
      Height = 15
      Caption = 'Veli'#269'ina fonta:'
    end
    object LSeparator: TLabel
      Left = 12
      Top = 73
      Width = 79
      Height = 15
      Caption = 'Vrsta razmaka:'
    end
    object LKeyboardLayout: TLabel
      Left = 13
      Top = 186
      Width = 89
      Height = 15
      Caption = 'Raspored tipki'
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
      Caption = 'Stani kod gre'#353'ke:'
      TabOrder = 1
      OnClick = CBMistakeClick
    end
    object CBConsecutiveMistakes: TCheckBox
      Left = 12
      Top = 254
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Broji uzastopne gre'#353'ke:'
      TabOrder = 2
      OnClick = CBConsecutiveMistakesClick
    end
    object CBSpeed: TCheckBox
      Left = 12
      Top = 284
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Prika'#382'i brzinu:'
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
      Caption = 'Prika'#382'i to'#269'nost:'
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
      Caption = 'Resetiraj'
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
    Caption = 'Odustani'
    ModalResult = 2
    TabOrder = 2
  end
  object BtAccept: TButton
    Left = 349
    Top = 435
    Width = 75
    Height = 25
    Caption = 'Prihvati'
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
