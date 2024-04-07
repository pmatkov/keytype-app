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
    Left = 33
    Top = 374
    Width = 50
    Height = 15
    Caption = 'Word list:'
    Transparent = True
  end
  object LTimeLimit: TLabel
    Left = 341
    Top = 374
    Width = 56
    Height = 15
    Caption = 'Time limit:'
  end
  inline FrFlyingWordsStatsFrame: TFrFlyingWordsStatsFrame
    Left = 0
    Top = 0
    Width = 628
    Height = 42
    TabOrder = 0
    inherited msgDisplayTimer: TTimer
      OnTimer = FrFlyingWordsStatsFramemsgDisplayTimerTimer
    end
  end
  object CBWordList: TComboBox
    Left = 89
    Top = 371
    Width = 103
    Height = 23
    Style = csDropDownList
    TabOrder = 1
    TabStop = False
    OnChange = CBWordListChange
  end
  object CBTime: TComboBox
    Left = 403
    Top = 371
    Width = 64
    Height = 23
    Style = csDropDownList
    TabOrder = 3
    TabStop = False
  end
  object BtBrowse: TButton
    Left = 210
    Top = 370
    Width = 75
    Height = 25
    Caption = 'Browse'
    TabOrder = 2
    TabStop = False
    OnClick = BtBrowseClick
  end
  object BtStartQuit: TButton
    Left = 495
    Top = 370
    Width = 75
    Height = 25
    Caption = 'Start game'
    TabOrder = 4
    TabStop = False
    OnClick = BtStartQuitClick
  end
  object DFileOpen: TOpenTextFileDialog
    Filter = 'Text files (*.txt)'
    Left = 258
    Top = 312
  end
end
