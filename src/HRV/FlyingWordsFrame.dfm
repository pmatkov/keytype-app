object FrFlyingWords: TFrFlyingWords
  Left = 0
  Top = 0
  Width = 628
  Height = 422
  DoubleBuffered = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  ParentDoubleBuffered = False
  ParentFont = False
  TabOrder = 0
  object LWordList: TLabel
    Left = 24
    Top = 374
    Width = 69
    Height = 15
    Caption = 'Word list file:'
    Transparent = True
  end
  object LTimeLimit: TLabel
    Left = 359
    Top = 374
    Width = 56
    Height = 15
    Caption = 'Vrem. limit:'
  end
  inline FrFlyingWordsStats: TFrFlyingWordsStats
    Left = 0
    Top = 0
    Width = 628
    Height = 42
    TabOrder = 0
    inherited TMsgDisplayTimer: TTimer
      OnTimer = FrFlyingWordsStatsFrameTMsgDisplayTimerTimer
      Left = 579
    end
  end
  object CBWordList: TComboBox
    Left = 116
    Top = 371
    Width = 103
    Height = 23
    Style = csDropDownList
    TabOrder = 1
    TabStop = False
    OnChange = CBWordListChange
  end
  object CBTime: TComboBox
    Left = 436
    Top = 371
    Width = 64
    Height = 23
    Style = csDropDownList
    TabOrder = 3
    TabStop = False
  end
  object BtBrowse: TButton
    Left = 240
    Top = 370
    Width = 75
    Height = 25
    Caption = 'Pretra'#382'i'
    TabOrder = 2
    TabStop = False
    OnClick = BtBrowseClick
  end
  object BtStartQuit: TButton
    Left = 525
    Top = 370
    Width = 75
    Height = 25
    Caption = 'Pokreni'
    TabOrder = 4
    TabStop = False
    OnClick = BtStartQuitClick
  end
  object DFileOpen: TOpenTextFileDialog
    Filter = 'Text files (*.txt)'
    Left = 570
    Top = 303
  end
end
