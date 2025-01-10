object FrTypingText: TFrTypingText
  Left = 0
  Top = 0
  Width = 328
  Height = 160
  TabOrder = 0
  object LPrompt: TLabel
    Left = 43
    Top = 125
    Width = 240
    Height = 17
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object REText: TRichEdit
    Left = 8
    Top = 6
    Width = 313
    Height = 100
    TabStop = False
    Alignment = taCenter
    BorderStyle = bsNone
    Color = clBtnFace
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
  end
end
