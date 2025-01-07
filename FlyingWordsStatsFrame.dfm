object FrFlyingWordsStats: TFrFlyingWordsStats
  Left = 0
  Top = 0
  Width = 628
  Height = 42
  TabOrder = 0
  object LLastWord: TLabel
    Left = 15
    Top = 15
    Width = 54
    Height = 15
    Caption = 'Last word:'
    Visible = False
  end
  object LLastWordDisplay: TLabel
    Left = 78
    Top = 15
    Width = 110
    Height = 15
    AutoSize = False
    Visible = False
  end
  object LTimeRemaining: TLabel
    Left = 355
    Top = 15
    Width = 86
    Height = 15
    Caption = 'Time remaining:'
    Visible = False
  end
  object LTimeRemainingDisplay: TLabel
    Left = 447
    Top = 15
    Width = 50
    Height = 15
    AutoSize = False
    Visible = False
  end
  object LMatchCount: TLabel
    Left = 200
    Top = 15
    Width = 87
    Height = 15
    Caption = 'Words matched:'
    Visible = False
  end
  object LPointsDisplay: TLabel
    Left = 553
    Top = 15
    Width = 50
    Height = 15
    AutoSize = False
    Visible = False
  end
  object LPoints: TLabel
    Left = 511
    Top = 15
    Width = 36
    Height = 15
    Caption = 'Points:'
    Visible = False
  end
  object LMatchCountDisplay: TLabel
    Left = 293
    Top = 15
    Width = 50
    Height = 15
    AutoSize = False
  end
  object TMsgDisplayTimer: TTimer
    Interval = 1500
    Left = 333
    Top = 3
  end
end
