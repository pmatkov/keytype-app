object FrGeneratedText: TFrGeneratedText
  Left = 0
  Top = 0
  Width = 517
  Height = 370
  TabOrder = 0
  object RGGeneratedText: TRadioGroup
    Left = 3
    Top = 0
    Width = 511
    Height = 41
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'Characters'
      'Words')
    TabOrder = 0
    OnClick = RGGeneratedTextClick
  end
  object GBCharacters: TGroupBox
    Left = 3
    Top = 47
    Width = 250
    Height = 314
    TabOrder = 1
    object BvCharSource: TBevel
      Left = 11
      Top = 104
      Width = 227
      Height = 2
      Shape = bsBottomLine
    end
    object TBLetters: TToolBar
      Left = 6
      Top = 12
      Width = 238
      Height = 80
      Align = alNone
      Caption = 'TBLetters'
      ShowCaptions = True
      TabOrder = 0
    end
    object CBSelectAll: TCheckBox
      Left = 11
      Top = 120
      Width = 77
      Height = 17
      Caption = 'Select all'
      TabOrder = 1
      OnClick = CBSelectAllClick
    end
    object CBNumbers: TCheckBox
      Left = 11
      Top = 149
      Width = 97
      Height = 17
      Caption = 'Numbers'
      TabOrder = 2
    end
    object CBPunctuation: TCheckBox
      Left = 138
      Top = 149
      Width = 97
      Height = 17
      Caption = 'Punctuation'
      TabOrder = 3
    end
    object CBCapitalLetters: TCheckBox
      Left = 138
      Top = 120
      Width = 97
      Height = 17
      Caption = 'Capital letters'
      TabOrder = 4
    end
  end
  object GBWords: TGroupBox
    Left = 264
    Top = 47
    Width = 250
    Height = 314
    TabOrder = 2
    object LWordList: TLabel
      Left = 12
      Top = 12
      Width = 50
      Height = 15
      Caption = 'Word list:'
    end
    object LDefinition: TLabel
      Left = 12
      Top = 196
      Width = 55
      Height = 15
      Caption = 'Definition:'
    end
    object LSynonym: TLabel
      Left = 12
      Top = 225
      Width = 58
      Height = 15
      Caption = 'Synonyms:'
    end
    object LCategory: TLabel
      Left = 13
      Top = 166
      Width = 51
      Height = 15
      Caption = 'Category:'
    end
    object LWord: TLabel
      Left = 12
      Top = 137
      Width = 32
      Height = 15
      Caption = 'Word:'
    end
    object LInfo: TLabel
      Left = 12
      Top = 285
      Width = 3
      Height = 15
    end
    object BtBrowse: TButton
      Left = 166
      Top = 8
      Width = 71
      Height = 25
      Caption = 'Browse'
      TabOrder = 0
      OnClick = BtBrowseClick
    end
    object CBTextFiles: TComboBox
      Left = 68
      Top = 9
      Width = 92
      Height = 23
      Style = csDropDownList
      TabOrder = 1
      OnChange = CBTextFilesChange
    end
    object LVWords: TListView
      Left = 12
      Top = 38
      Width = 225
      Height = 90
      Columns = <>
      MultiSelect = True
      ReadOnly = True
      TabOrder = 2
      ViewStyle = vsList
      OnMouseDown = LVWordsMouseDown
      OnSelectItem = LVWordsSelectItem
    end
    object EWord: TEdit
      Left = 88
      Top = 134
      Width = 149
      Height = 23
      TabOrder = 3
    end
    object EDefinition: TEdit
      Left = 88
      Top = 192
      Width = 149
      Height = 23
      TabOrder = 4
    end
    object ESynonyms: TEdit
      Left = 88
      Top = 221
      Width = 149
      Height = 23
      TabOrder = 5
    end
    object CBCategory: TComboBox
      Left = 88
      Top = 163
      Width = 149
      Height = 23
      Style = csDropDownList
      TabOrder = 6
    end
    object BtAddSave1: TButton
      Left = 180
      Top = 280
      Width = 57
      Height = 23
      Caption = 'Add'
      TabOrder = 7
      OnClick = BtAddSave1Click
    end
    object BtDelete1: TButton
      Left = 104
      Top = 280
      Width = 56
      Height = 23
      Caption = 'Delete'
      Enabled = False
      TabOrder = 8
      OnClick = BtDelete1Click
    end
  end
  object DFileOpen: TOpenTextFileDialog
    Filter = 'Text files (*.txt)'
    Left = 336
    Top = 113
  end
  object msgDisplayTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = msgDisplayTimerTimer
    Left = 192
    Top = 284
  end
end
