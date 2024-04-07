object FrFlyingWordsStatsFrame: TFrFlyingWordsStatsFrame
  Left = 0
  Top = 0
  Width = 628
  Height = 42
  TabOrder = 0
  object LLastWord: TLabel
    Left = 18
    Top = 15
    Width = 54
    Height = 15
    Caption = 'Last word:'
    Visible = False
  end
  object LLastWordDisplay: TLabel
    Left = 78
    Top = 15
    Width = 100
    Height = 15
    AutoSize = False
    Visible = False
  end
  object LTimeRemaining: TLabel
    Left = 349
    Top = 15
    Width = 86
    Height = 15
    Caption = 'Time remaining:'
    Visible = False
  end
  object LTimeRemainingDisplay: TLabel
    Left = 441
    Top = 15
    Width = 50
    Height = 15
    AutoSize = False
    Visible = False
  end
  object LMatchCount: TLabel
    Left = 194
    Top = 15
    Width = 87
    Height = 15
    Caption = 'Words matched:'
    Visible = False
  end
  object LPointsDisplay: TLabel
    Left = 547
    Top = 15
    Width = 50
    Height = 15
    AutoSize = False
    Visible = False
  end
  object LPoints: TLabel
    Left = 505
    Top = 15
    Width = 36
    Height = 15
    Caption = 'Points:'
    Visible = False
  end
  object LMatchCountDisplay: TLabel
    Left = 287
    Top = 15
    Width = 50
    Height = 15
    AutoSize = False
  end
  object msgDisplayTimer: TTimer
    Interval = 1500
    Left = 597
    Top = 12
  end
end
