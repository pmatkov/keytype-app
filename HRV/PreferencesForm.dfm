object FPreferences: TFPreferences
  Left = 0
  Top = 0
  Caption = 'Preferences'
  ClientHeight = 446
  ClientWidth = 542
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object GroupBox1: TGroupBox
    Left = 8
    Top = 27
    Width = 254
    Height = 343
    Caption = 'Postavke aplikacije'
    TabOrder = 0
    object LLanguage: TLabel
      Left = 12
      Top = 45
      Width = 55
      Height = 15
      Caption = 'Jezik:'
    end
    object LLogging: TLabel
      Left = 12
      Top = 147
      Width = 47
      Height = 15
      Caption = 'Bilje'#382'enje:'
    end
    object LFont1: TLabel
      Left = 12
      Top = 81
      Width = 63
      Height = 15
      Caption = 'Vrsta fonta:'
    end
    object CBLanguage: TComboBox
      Left = 126
      Top = 42
      Width = 115
      Height = 23
      TabOrder = 0
      Items.Strings = (
        'Engleski'
        'Hrvatski')
    end
    object CBLogging: TComboBox
      Left = 126
      Top = 144
      Width = 115
      Height = 23
      TabOrder = 1
    end
    object CBLoggingEnable: TCheckBox
      Left = 93
      Top = 147
      Width = 16
      Height = 17
      TabOrder = 2
    end
    object CBFont1: TComboBox
      Left = 126
      Top = 78
      Width = 115
      Height = 23
      TabOrder = 3
    end
    object BtReset1: TButton
      Left = 166
      Top = 297
      Width = 75
      Height = 25
      Caption = 'Resetiraj'
      TabOrder = 4
    end
  end
  object GroupBox2: TGroupBox
    Left = 280
    Top = 27
    Width = 254
    Height = 343
    Caption = 'Postavke tipkanja'
    TabOrder = 1
    object LCaret: TLabel
      Left = 12
      Top = 45
      Width = 57
      Height = 15
      Caption = 'Pokaziva'#269':'
    end
    object LFont2: TLabel
      Left = 12
      Top = 81
      Width = 63
      Height = 15
      Caption = 'Vrsta fonta:'
    end
    object LFontSize: TLabel
      Left = 12
      Top = 121
      Width = 49
      Height = 15
      Caption = 'Veli'#269'ina fonta:'
    end
    object CBCaret: TComboBox
      Left = 126
      Top = 42
      Width = 115
      Height = 23
      TabOrder = 0
      Items.Strings = (
        'Vertikalna crta'
        'Potcrtano')
    end
    object CBMistake: TCheckBox
      Left = 12
      Top = 159
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Stani kod pogre'#353'ke:'
      TabOrder = 1
    end
    object CBSeqMistakes: TCheckBox
      Left = 12
      Top = 192
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Broji uzastopne pogre'#353'ke:'
      TabOrder = 2
    end
    object CBSpeed: TCheckBox
      Left = 12
      Top = 225
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Prika'#382'i brzinu:'
      TabOrder = 3
    end
    object CBFont2: TComboBox
      Left = 126
      Top = 78
      Width = 115
      Height = 23
      TabOrder = 4
    end
    object CBAccuracy: TCheckBox
      Left = 12
      Top = 258
      Width = 229
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Prika'#382'i to'#269'nost:'
      TabOrder = 5
    end
    object ComboBox1: TComboBox
      Left = 126
      Top = 118
      Width = 115
      Height = 23
      TabOrder = 6
      Items.Strings = (
        '9'
        '10'
        '12'
        '14')
    end
    object BtReset2: TButton
      Left = 165
      Top = 297
      Width = 75
      Height = 25
      Caption = 'Resetiraj'
      TabOrder = 7
    end
  end
  object BtCancel: TButton
    Left = 449
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Otka'#382'i'
    ModalResult = 2
    TabOrder = 2
  end
  object BtAccept: TButton
    Left = 352
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Prihvati'
    ModalResult = 1
    TabOrder = 3
  end
end
