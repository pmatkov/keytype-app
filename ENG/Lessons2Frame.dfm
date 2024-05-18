object FrLessons2: TFrLessons2
  Left = 0
  Top = 0
  Width = 628
  Height = 422
  TabOrder = 0
  object LChars: TLabel
    Left = 14
    Top = 105
    Width = 33
    Height = 15
    Caption = 'Chars:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LWords: TLabel
    Left = 14
    Top = 129
    Width = 37
    Height = 15
    Caption = 'Words:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LCharsDisplay: TLabel
    Left = 111
    Top = 105
    Width = 25
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LWordsDisplay: TLabel
    Left = 111
    Top = 129
    Width = 25
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LGoal: TLabel
    Left = 14
    Top = 213
    Width = 27
    Height = 15
    Caption = 'Goal:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LGoalDisplay: TLabel
    Left = 51
    Top = 213
    Width = 85
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LDifficulty: TLabel
    Left = 14
    Top = 187
    Width = 51
    Height = 15
    Caption = 'Difficulty:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LDifficultyDisplay: TLabel
    Left = 111
    Top = 187
    Width = 25
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object LLessonResult: TLabel
    Left = 189
    Top = 372
    Width = 71
    Height = 15
    Caption = 'Lesson result:'
    Visible = False
  end
  object LLessonResultDisplay: TLabel
    Left = 272
    Top = 372
    Width = 204
    Height = 15
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object CBSelectCourse: TComboBox
    Left = 486
    Top = 102
    Width = 130
    Height = 23
    Style = csDropDownList
    TabOrder = 0
    OnChange = CBSelectCourseChange
  end
  object CBSelectLesson: TComboBox
    Left = 486
    Top = 139
    Width = 130
    Height = 23
    Style = csDropDownList
    TabOrder = 1
    OnChange = CBSelectLessonChange
  end
  inline FrTypingStats: TFrTypingStats
    Left = 0
    Top = 20
    Width = 628
    Height = 60
    TabOrder = 2
    ExplicitTop = 20
    inherited LDisplayAccuracy: TLabel
      Width = 60
      ExplicitWidth = 60
    end
  end
  object MInstructions: TMemo
    Left = 161
    Top = 102
    Width = 300
    Height = 60
    Enabled = False
    ReadOnly = True
    TabOrder = 3
  end
  inline FrTypingText: TFrTypingText
    Left = 149
    Top = 187
    Width = 327
    Height = 160
    TabOrder = 4
    ExplicitLeft = 149
    ExplicitTop = 187
    inherited LPrompt: TLabel
      Left = 17
      Top = 122
      ExplicitLeft = 17
      ExplicitTop = 122
    end
    inherited REText: TRichEdit
      Left = 8
      Top = 3
      BorderStyle = bsSingle
      ExplicitLeft = 8
      ExplicitTop = 3
    end
  end
  object BtStartQuit: TButton
    Left = 531
    Top = 190
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 5
    OnClick = BtStartQuitClick
  end
end
