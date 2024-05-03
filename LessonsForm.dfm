object FLessons: TFLessons
  Left = 0
  Top = 0
  Caption = 'Configuration'
  ClientHeight = 444
  ClientWidth = 530
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object BtAccept: TButton
    Left = 447
    Top = 411
    Width = 75
    Height = 25
    Caption = 'Accept'
    ModalResult = 1
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
