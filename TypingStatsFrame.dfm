object FrTypingStats: TFrTypingStats
  Left = 0
  Top = 0
  Width = 628
  Height = 60
  TabOrder = 0
  object LTime: TLabel
    Left = 101
    Top = 20
    Width = 29
    Height = 15
    Caption = 'Time:'
  end
  object LDisplayTime: TLabel
    Left = 136
    Top = 20
    Width = 50
    Height = 15
    AutoSize = False
  end
  object LSpeed: TLabel
    Left = 216
    Top = 20
    Width = 35
    Height = 15
    Caption = 'Speed:'
  end
  object LDisplaySpeed: TLabel
    Left = 257
    Top = 20
    Width = 60
    Height = 15
    AutoSize = False
  end
  object LAccuracy: TLabel
    Left = 345
    Top = 20
    Width = 52
    Height = 15
    Caption = 'Accuracy:'
  end
  object LDisplayAccuracy: TLabel
    Left = 403
    Top = 20
    Width = 50
    Height = 15
    AutoSize = False
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 510
    Top = 9
  end
end
