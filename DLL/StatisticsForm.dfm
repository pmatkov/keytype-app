object FStatistics: TFStatistics
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Statistics'
  ClientHeight = 422
  ClientWidth = 588
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object LMostAccurateChar: TLabel
    Left = 33
    Top = 396
    Width = 104
    Height = 15
    Caption = 'Most accurate char:'
  end
  object LMostAccurateCharDisplay: TLabel
    Left = 143
    Top = 396
    Width = 20
    Height = 15
    AutoSize = False
  end
  object LLeastAccurateChar: TLabel
    Left = 201
    Top = 396
    Width = 104
    Height = 15
    Caption = 'Least accurate char:'
  end
  object LLeastAccurateCharDisplay: TLabel
    Left = 311
    Top = 396
    Width = 20
    Height = 15
    AutoSize = False
  end
  object LAveragePracticeTime: TLabel
    Left = 363
    Top = 396
    Width = 118
    Height = 15
    Caption = 'Average practice time:'
  end
  object LAveragePracticeTimeDisplay: TLabel
    Left = 487
    Top = 396
    Width = 50
    Height = 15
    AutoSize = False
  end
  object ChPracticeTime: TChart
    Left = 15
    Top = 12
    Width = 556
    Height = 178
    Legend.Visible = False
    Title.Font.Color = clBlack
    Title.Font.Height = -13
    Title.Font.Style = [fsBold, fsItalic]
    Title.Frame.Visible = False
    Title.Shadow.Visible = False
    Title.ShapeCallout.Size = 22
    Title.Text.Strings = (
      'Practice time')
    Title.VertMargin = 8
    BottomAxis.Title.Caption = 'Date'
    LeftAxis.Title.Caption = 'Time (min)'
    View3D = False
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 15
    object STime: TBarSeries
      HoverElement = []
      ColorEachPoint = True
      Marks.Visible = False
      Marks.Symbol.Frame.Visible = False
      Marks.Symbol.Pen.Visible = False
      SeriesColor = 12615680
      Title = 'Time'
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
  end
  object ChAccuracyChar: TChart
    Left = 15
    Top = 201
    Width = 556
    Height = 178
    Legend.Alignment = laBottom
    Title.Font.Color = clBlack
    Title.Font.Height = -13
    Title.Font.Style = [fsBold, fsItalic]
    Title.Text.Strings = (
      'Accuracy per char')
    BottomAxis.Title.Caption = 'Char'
    LeftAxis.Title.Caption = 'Char count'
    View3D = False
    TabOrder = 1
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 15
    object SCorrect: TBarSeries
      HoverElement = []
      Marks.Visible = False
      SeriesColor = 12499290
      Title = 'Correct'
      MultiBar = mbStacked
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
    object SMistake: TBarSeries
      HoverElement = []
      Marks.Visible = False
      SeriesColor = 4145120
      Title = 'Mistake'
      MultiBar = mbStacked
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
  end
end
