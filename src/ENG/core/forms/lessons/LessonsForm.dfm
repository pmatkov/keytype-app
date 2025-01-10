object FLessons: TFLessons
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Configuration'
  ClientHeight = 442
  ClientWidth = 526
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object BtClose: TButton
    Left = 447
    Top = 410
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 0
  end
  object PCLessons: TPageControl
    Left = 8
    Top = 8
    Width = 514
    Height = 395
    ActivePage = TSCourses
    TabOrder = 1
    object TSCourses: TTabSheet
      Caption = 'Courses'
    end
    object TSLessons: TTabSheet
      Caption = 'Lessons'
      ImageIndex = 1
    end
  end
end
