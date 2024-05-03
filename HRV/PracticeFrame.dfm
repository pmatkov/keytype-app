object FrPractice: TFrPractice
  Left = 0
  Top = 0
  Width = 628
  Height = 422
  TabOrder = 0
  inline FrTypingStats: TFrTypingStats
    Left = 0
    Top = 66
    Width = 628
    Height = 60
    TabOrder = 0
    ExplicitTop = 66
  end
  object BtOptions: TButton
    Left = 497
    Top = 142
    Width = 78
    Height = 30
    Margins.Left = 10
    Margins.Top = 10
    Margins.Right = 10
    Margins.Bottom = 10
    Caption = 'Options'
    ImageIndex = 0
    ImageMargins.Left = 5
    ImageMargins.Top = 5
    ImageMargins.Bottom = 5
    TabOrder = 1
    TabStop = False
    OnClick = FrOptionsBtOptionsClick
  end
  inline FrTypingText: TFrTypingText
    Left = 104
    Top = 142
    Width = 339
    Height = 165
    TabOrder = 2
    ExplicitLeft = 104
    ExplicitTop = 142
    ExplicitHeight = 165
  end
end
