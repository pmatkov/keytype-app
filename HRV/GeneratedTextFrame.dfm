object FrGeneratedText: TFrGeneratedText
  Left = 0
  Top = 0
  Width = 504
  Height = 360
  TabOrder = 0
  object GBWords: TGroupBox
    Left = 6
    Top = 3
    Width = 489
    Height = 348
    TabOrder = 0
    object LDictionary: TLabel
      Left = 15
      Top = 15
      Width = 76
      Height = 15
      Caption = 'Rje'#269'nik:'
    end
    object LDefinition: TLabel
      Left = 12
      Top = 237
      Width = 55
      Height = 15
      Caption = 'Definicija:'
    end
    object LSynonym: TLabel
      Left = 12
      Top = 268
      Width = 58
      Height = 15
      Caption = 'Sinonimi:'
    end
    object LCategory: TLabel
      Left = 12
      Top = 202
      Width = 51
      Height = 15
      Caption = 'Kategorija:'
    end
    object LWord: TLabel
      Left = 15
      Top = 170
      Width = 32
      Height = 15
      Caption = 'Riije'#269':'
    end
    object LInfo: TLabel
      Left = 15
      Top = 314
      Width = 65
      Height = 15
      AutoSize = False
    end
    object LWordsMin: TLabel
      Left = 270
      Top = 170
      Width = 61
      Height = 15
      Caption = 'Rije'#269'i min:'
    end
    object LWordsMax: TLabel
      Left = 397
      Top = 170
      Width = 26
      Height = 15
      Caption = 'max:'
    end
    object BtBrowse: TButton
      Left = 235
      Top = 11
      Width = 71
      Height = 25
      Caption = 'Pretra'#382'i:'
      TabOrder = 0
      OnClick = BtBrowseClick
    end
    object CBDictionaryFiles: TComboBox
      Left = 102
      Top = 12
      Width = 121
      Height = 23
      Style = csDropDownList
      TabOrder = 1
      OnChange = CBDictionaryFilesChange
    end
    object LVDictionary: TListView
      Left = 12
      Top = 45
      Width = 466
      Height = 106
      Columns = <
        item
          Caption = 'Rije'#269
          Width = 80
        end
        item
          Caption = 'Category'
          Width = 100
        end
        item
          Caption = 'Definition'
          Width = 160
        end
        item
          Caption = 'Sinonimi'
          Width = 120
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 2
      ViewStyle = vsReport
      OnMouseDown = LVDictionaryMouseDown
      OnSelectItem = LVDictionarySelectItem
    end
    object EWord: TEdit
      Left = 90
      Top = 167
      Width = 133
      Height = 23
      TabOrder = 3
    end
    object EDefinition: TEdit
      Left = 90
      Top = 234
      Width = 133
      Height = 23
      TabOrder = 4
    end
    object ESynonyms: TEdit
      Left = 90
      Top = 265
      Width = 133
      Height = 23
      TabOrder = 5
    end
    object CBCategory: TComboBox
      Left = 90
      Top = 199
      Width = 133
      Height = 23
      Style = csDropDownList
      TabOrder = 6
    end
    object BtAddSave1: TButton
      Left = 166
      Top = 311
      Width = 57
      Height = 23
      Caption = 'Dodaj'
      TabOrder = 7
      OnClick = BtAddSave1Click
    end
    object BtDelete1: TButton
      Left = 90
      Top = 311
      Width = 56
      Height = 23
      Caption = 'Obri'#353'i'
      Enabled = False
      TabOrder = 8
      OnClick = BtDelete1Click
    end
    object CBWordsMin: TComboBox
      Left = 337
      Top = 167
      Width = 45
      Height = 23
      Style = csDropDownList
      TabOrder = 9
    end
    object CBWordsMax: TComboBox
      Left = 433
      Top = 167
      Width = 45
      Height = 23
      Style = csDropDownList
      TabOrder = 10
    end
    object CBNumbers: TCheckBox
      Left = 270
      Top = 202
      Width = 88
      Height = 17
      BiDiMode = bdRightToLeft
      Caption = 'Brojevi'
      ParentBiDiMode = False
      TabOrder = 11
    end
    object CBPunctuation: TCheckBox
      Left = 367
      Top = 202
      Width = 111
      Height = 17
      BiDiMode = bdRightToLeft
      Caption = 'Interpunkcija'
      ParentBiDiMode = False
      TabOrder = 12
    end
    object MPreview: TMemo
      Left = 270
      Top = 231
      Width = 208
      Height = 52
      Lines.Strings = (
        '')
      TabOrder = 13
    end
    object BtTest: TButton
      Left = 403
      Top = 310
      Width = 75
      Height = 25
      Caption = 'Test'
      TabOrder = 14
    end
    object BtTestThreads: TButton
      Left = 316
      Top = 310
      Width = 75
      Height = 25
      Caption = 'Test [T]'
      TabOrder = 15
    end
    object BtConvert: TButton
      Left = 403
      Top = 11
      Width = 75
      Height = 25
      Caption = 'Konverter'
      TabOrder = 16
      OnClick = BtConvertClick
    end
  end
  object DFileOpen: TOpenTextFileDialog
    Left = 243
    Top = 287
  end
  object msgDisplayTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = msgDisplayTimerTimer
    Left = 246
    Top = 215
  end
end
