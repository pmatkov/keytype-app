object FrCourses: TFrCourses
  Left = 0
  Top = 0
  Width = 506
  Height = 365
  TabOrder = 0
  object GBCourses: TGroupBox
    Left = 6
    Top = 3
    Width = 491
    Height = 352
    TabOrder = 2
    object LName: TLabel
      Left = 13
      Top = 243
      Width = 30
      Height = 15
      Caption = 'naziv'
    end
    object LDescription: TLabel
      Left = 93
      Top = 243
      Width = 59
      Height = 15
      Caption = 'opis'
    end
    object LDifficulty: TLabel
      Left = 216
      Top = 243
      Width = 47
      Height = 15
      Caption = 'te'#382'ina'
    end
    object LGoal: TLabel
      Left = 273
      Top = 240
      Width = 23
      Height = 15
      Caption = 'cilj'
    end
    object LLanguage: TLabel
      Left = 408
      Top = 243
      Width = 49
      Height = 15
      Caption = 'jezik'
    end
    object LGoalValue: TLabel
      Left = 354
      Top = 243
      Width = 41
      Height = 15
      Caption = 'cilj vr.'
    end
    object BtClearSelection: TButton
      Left = 13
      Top = 303
      Width = 75
      Height = 25
      Caption = 'Deselektiraj'
      TabOrder = 0
      OnClick = BtClearSelectionClick
    end
    object EName: TEdit
      Left = 13
      Top = 261
      Width = 64
      Height = 23
      TabOrder = 1
    end
    object EDescription: TEdit
      Left = 87
      Top = 261
      Width = 121
      Height = 23
      TabOrder = 2
    end
    object CBDifficulty: TComboBox
      Left = 216
      Top = 261
      Width = 47
      Height = 23
      Style = csDropDownList
      TabOrder = 3
      Items.Strings = (
        '1'
        '2'
        '3')
    end
    object CBGoal: TComboBox
      Left = 273
      Top = 261
      Width = 70
      Height = 23
      Style = csDropDownList
      TabOrder = 4
      Items.Strings = (
        'accuracy'
        'speed')
    end
    object CBLanguage: TComboBox
      Left = 408
      Top = 261
      Width = 72
      Height = 23
      Style = csDropDownList
      TabOrder = 5
      Items.Strings = (
        'English'
        'Croatian')
    end
    object CBFilter: TComboBox
      Left = 3
      Top = 10
      Width = 85
      Height = 23
      Style = csDropDownList
      TabOrder = 6
    end
    object EFilter: TEdit
      Left = 99
      Top = 10
      Width = 50
      Height = 23
      TabOrder = 7
    end
    object BtFilter: TButton
      Left = 155
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Filtriraj'
      TabOrder = 8
      OnClick = BtFilterClick
    end
    object ESort: TEdit
      Left = 277
      Top = 10
      Width = 121
      Height = 23
      TabOrder = 9
    end
    object BtSort: TButton
      Left = 404
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Sortiraj'
      TabOrder = 10
      OnClick = BtSortClick
    end
    object EGoalValue: TEdit
      Left = 354
      Top = 261
      Width = 48
      Height = 23
      TabOrder = 11
    end
  end
  object DBGridCourses: TDBGrid
    Left = 6
    Top = 50
    Width = 491
    Height = 190
    DataSource = DataModule1.DCourses
    Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    OnCellClick = DBGridCoursesCellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'id'
        Width = 20
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name'
        Title.Caption = 'Naziv'
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'description'
        Title.Caption = 'Opis'
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'difficulty'
        Title.Caption = 'Te'#382'ina'
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'goal'
        Title.Caption = 'Cilj'
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'goalValue'
        Title.Caption = 'Cilj vr.'
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'language'
        Title.Caption = 'Jezik'
        Width = 80
        Visible = True
      end>
  end
  object BtDelete: TButton
    Left = 327
    Top = 306
    Width = 75
    Height = 25
    Caption = 'Obri'#353'i'
    TabOrder = 1
    OnClick = BtDeleteClick
  end
  object BtAddSave: TButton
    Left = 408
    Top = 306
    Width = 75
    Height = 25
    Caption = 'Dodaj'
    TabOrder = 3
    OnClick = BtAddSaveClick
  end
end
