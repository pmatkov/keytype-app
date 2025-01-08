object FrLessons: TFrLessons
  Left = 0
  Top = 0
  Width = 506
  Height = 365
  TabOrder = 0
  object GBLessons: TGroupBox
    Left = 6
    Top = 3
    Width = 491
    Height = 352
    TabOrder = 1
    object LInstructions: TLabel
      Left = 87
      Top = 243
      Width = 62
      Height = 15
      Caption = 'upute'
    end
    object LName: TLabel
      Left = 13
      Top = 243
      Width = 30
      Height = 15
      Caption = 'naziv'
    end
    object LCharacters: TLabel
      Left = 197
      Top = 243
      Width = 54
      Height = 15
      Caption = 'znakovi'
    end
    object LWordCount: TLabel
      Left = 267
      Top = 243
      Width = 61
      Height = 15
      Caption = 'br. rije'#269'i'
    end
    object LDateModified: TLabel
      Left = 405
      Top = 243
      Width = 74
      Height = 15
      Caption = 'datum izmjene'
    end
    object LCharCount: TLabel
      Left = 337
      Top = 243
      Width = 57
      Height = 15
      Caption = 'br. znakova'
    end
    object BtDelete: TButton
      Left = 323
      Top = 303
      Width = 75
      Height = 25
      Caption = 'Obri'#353'i'
      TabOrder = 1
      OnClick = BtDeleteClick
    end
    object BtAddSave: TButton
      Left = 404
      Top = 303
      Width = 75
      Height = 25
      Caption = 'Dodaj'
      TabOrder = 0
      OnClick = BtAddSaveClick
    end
    object EName: TEdit
      Left = 13
      Top = 261
      Width = 64
      Height = 23
      TabOrder = 2
    end
    object BtClearSelection: TButton
      Left = 13
      Top = 303
      Width = 75
      Height = 25
      Caption = 'Deselektiraj'
      TabOrder = 3
      OnClick = BtClearSelectionClick
    end
    object EInstructions: TEdit
      Left = 87
      Top = 261
      Width = 100
      Height = 23
      TabOrder = 4
    end
    object ECharacters: TEdit
      Left = 197
      Top = 261
      Width = 64
      Height = 23
      TabOrder = 5
    end
    object EWordCount: TEdit
      Left = 267
      Top = 261
      Width = 64
      Height = 23
      TabOrder = 6
    end
    object EDateModified: TEdit
      Left = 408
      Top = 261
      Width = 71
      Height = 23
      TabOrder = 7
    end
    object CBFilter: TComboBox
      Left = 3
      Top = 10
      Width = 85
      Height = 23
      Style = csDropDownList
      TabOrder = 8
    end
    object EFilter: TEdit
      Left = 99
      Top = 10
      Width = 50
      Height = 23
      TabOrder = 9
    end
    object BtFilter: TButton
      Left = 155
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Filtriraj'
      TabOrder = 10
      OnClick = BtFilterClick
    end
    object ECharCount: TEdit
      Left = 337
      Top = 261
      Width = 66
      Height = 23
      TabOrder = 11
    end
    object BtSort: TButton
      Left = 404
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Sortiraj'
      TabOrder = 12
      OnClick = BtSortClick
    end
    object ESort: TEdit
      Left = 277
      Top = 10
      Width = 121
      Height = 23
      TabOrder = 13
    end
    object BtMasterDetail: TButton
      Left = 94
      Top = 303
      Width = 75
      Height = 25
      Caption = 'Isklj. master'
      TabOrder = 14
      OnClick = BtMasterDetailClick
    end
  end
  object DBGridLessons: TDBGrid
    Left = 6
    Top = 50
    Width = 491
    Height = 190
    DataSource = DataModule1.DLessons
    Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    OnCellClick = DBGridLessonsCellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'id'
        Width = 20
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'id kursa'
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'courseName'
        Title.Caption = 'Naziv kursa'
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name'
        Title.Caption = 'Naziv lekc.'
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'instructions'
        Title.Caption = 'Upute'
        Width = 110
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'characters'
        Title.Caption = 'Znakovi'
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'charCount'
        Title.Caption = 'Br. znakova'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'wordCount'
        Title.Caption = 'Br. rije'#269'i'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'avgChars'
        Title.Caption = 'Prosj. znakova'
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'dateModified'
        Title.Caption = 'Datum izmjene'
        Visible = True
      end>
  end
end
