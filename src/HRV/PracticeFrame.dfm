object FrPractice: TFrPractice
  Left = 0
  Top = 0
  Width = 628
  Height = 422
  TabOrder = 0
  object LPracticeResult: TLabel
    Left = 133
    Top = 393
    Width = 77
    Height = 15
    Caption = 'Rezultat vje'#382'be:'
    Visible = False
  end
  object LPracticeResultDisplay: TLabel
    Left = 216
    Top = 393
    Width = 204
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LKeyboardLayout: TLabel
    Left = 462
    Top = 249
    Width = 140
    Height = 15
    AutoSize = False
  end
  inline FrTypingStats: TFrTypingStats
    Left = 0
    Top = 15
    Width = 628
    Height = 60
    TabOrder = 0
    ExplicitTop = 15
    inherited TStatsTimer: TTimer
      Left = 522
    end
  end
  object BtStartQuit: TButton
    Left = 460
    Top = 190
    Width = 90
    Height = 25
    Caption = 'Pokreni'
    TabOrder = 1
    OnClick = BtStartQuitClick
  end
  inline FrTypingText: TFrTypingText
    Left = 114
    Top = 81
    Width = 328
    Height = 160
    TabOrder = 2
    ExplicitLeft = 114
    ExplicitTop = 81
    inherited REText: TRichEdit
      Top = 7
      BorderStyle = bsSingle
      ExplicitTop = 7
    end
  end
  object PPracticeType: TPanel
    Left = 460
    Top = 88
    Width = 150
    Height = 40
    ParentBackground = False
    TabOrder = 3
    object SBtPracticeType1: TSpeedButton
      Left = 13
      Top = 10
      Width = 55
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = 'Rije'#269'i'
    end
    object SBtPracticeType2: TSpeedButton
      Left = 83
      Top = 10
      Width = 55
      Height = 22
      GroupIndex = 1
      Caption = 'Vrijeme'
    end
  end
  object PPracticeLimit: TPanel
    Left = 460
    Top = 134
    Width = 150
    Height = 40
    TabOrder = 4
    object SBtPracticeLimit1: TSpeedButton
      Left = 14
      Top = 9
      Width = 22
      Height = 22
      GroupIndex = 2
      Down = True
      Caption = '10'
    end
    object SBtPracticeLimit2: TSpeedButton
      Left = 47
      Top = 9
      Width = 22
      Height = 22
      GroupIndex = 2
      Caption = '25'
    end
    object SBtPracticeLimit3: TSpeedButton
      Left = 88
      Top = 9
      Width = 22
      Height = 22
      GroupIndex = 2
      Caption = '50'
    end
    object SBtPracticeLimit4: TSpeedButton
      Left = 116
      Top = 9
      Width = 22
      Height = 22
      GroupIndex = 2
      Caption = '75'
    end
  end
  object BtConfig: TBitBtn
    Left = 575
    Top = 190
    Width = 35
    Height = 25
    TabOrder = 5
    OnClick = BtConfigClick
  end
  inline FrKeyboard: TFrKeyboard
    Left = 114
    Top = 249
    Width = 332
    Height = 138
    TabOrder = 6
    ExplicitLeft = 114
    ExplicitTop = 249
  end
end
