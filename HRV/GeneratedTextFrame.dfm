object FrGeneratedText: TFrGeneratedText
  Left = 0
  Top = 0
  Width = 504
  Height = 400
  TabOrder = 0
  object GBWords: TGroupBox
    Left = 6
    Top = 3
    Width = 489
    Height = 391
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
      Top = 239
      Width = 55
      Height = 15
      Caption = 'Definicija:'
    end
    object LSynonym: TLabel
      Left = 12
      Top = 271
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
      Left = 12
      Top = 347
      Width = 78
      Height = 15
      AutoSize = False
    end
    object LWordsMin: TLabel
      Left = 258
      Top = 202
      Width = 61
      Height = 15
      Caption = 'Rije'#269'i min:'
    end
    object LWordsMax: TLabel
      Left = 406
      Top = 202
      Width = 26
      Height = 15
      Caption = 'max:'
    end
    object LCharsWordMax: TLabel
      Left = 406
      Top = 170
      Width = 26
      Height = 15
      Caption = 'max:'
    end
    object LCharsWordMin: TLabel
      Left = 258
      Top = 170
      Width = 92
      Height = 15
      Caption = 'Znakova/ rije'#269'i min:'
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
      Height = 109
      Columns = <
        item
          Caption = 'Rije'#269
          Width = 80
        end
        item
          Caption = 'Kategorija'
          Width = 100
        end
        item
          Caption = 'Definicija'
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
      Top = 231
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
      Left = 167
      Top = 305
      Width = 56
      Height = 23
      Caption = 'Dodaj'
      TabOrder = 7
      OnClick = BtAddSave1Click
    end
    object BtDelete1: TButton
      Left = 102
      Top = 305
      Width = 56
      Height = 23
      Caption = 'Obri'#353'i'
      Enabled = False
      TabOrder = 8
      OnClick = BtDelete1Click
    end
    object CBCharsWordMin: TComboBox
      Left = 362
      Top = 167
      Width = 38
      Height = 23
      Style = csDropDownList
      TabOrder = 9
    end
    object CBCharsWordMax: TComboBox
      Left = 438
      Top = 167
      Width = 38
      Height = 23
      Style = csDropDownList
      TabOrder = 10
    end
    object CBSynonyms: TCheckBox
      Left = 376
      Top = 234
      Width = 102
      Height = 17
      Alignment = taLeftJustify
      BiDiMode = bdLeftToRight
      Caption = 'Sinononi:'
      ParentBiDiMode = False
      TabOrder = 11
    end
    object MPreview: TMemo
      Left = 258
      Top = 265
      Width = 220
      Height = 64
      Lines.Strings = (
        'Pregled generiranog teksta')
      ReadOnly = True
      TabOrder = 12
    end
    object BtGenerate: TButton
      Left = 403
      Top = 343
      Width = 75
      Height = 25
      Caption = 'Generiraj'
      TabOrder = 13
      OnClick = BtGenerateClick
    end
    object BtConvert: TButton
      Left = 403
      Top = 11
      Width = 75
      Height = 25
      Caption = 'Konverter'
      TabOrder = 14
      OnClick = BtConvertClick
    end
    object CBWordsMax: TComboBox
      Left = 438
      Top = 199
      Width = 38
      Height = 23
      Style = csDropDownList
      TabOrder = 15
    end
    object BtShuffle: TButton
      Left = 315
      Top = 343
      Width = 75
      Height = 25
      Caption = 'Izmije'#353'aj'
      TabOrder = 16
      OnClick = BtShuffleClick
    end
    object BtSynonyms: TButton
      Left = 12
      Top = 304
      Width = 62
      Height = 25
      Caption = 'Dohvati @'
      TabOrder = 17
      OnClick = BtSynonymsClick
    end
    object CBUppercase: TCheckBox
      Left = 256
      Top = 234
      Width = 106
      Height = 17
      Alignment = taLeftJustify
      BiDiMode = bdLeftToRight
      Caption = 'Velika slova:'
      ParentBiDiMode = False
      TabOrder = 18
    end
  end
  object CBWordsMin: TComboBox
    Left = 368
    Top = 202
    Width = 38
    Height = 23
    Style = csDropDownList
    TabOrder = 1
  end
  object DFileOpen: TOpenTextFileDialog
    Left = 156
    Top = 98
  end
  object msgDisplayTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = msgDisplayTimerTimer
    Left = 66
    Top = 98
  end
end
