object FrFlyingWords: TFrFlyingWords
  Left = 0
  Top = 0
  Width = 628
  Height = 422
  TabOrder = 0
  object LStart: TLabel
    Left = 258
    Top = 330
    Width = 120
    Height = 15
    AutoSize = False
    Caption = 'Click to start the game'
    OnClick = LStartClick
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 10
    Left = 432
    Top = 318
  end
end
