object FPractice: TFPractice
  Left = 0
  Top = 0
  Caption = 'Select a text source'
  ClientHeight = 426
  ClientWidth = 521
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnShow = FormShow
  TextHeight = 15
  object PCSourceText: TPageControl
    Left = 8
    Top = 8
    Width = 509
    Height = 373
    ActivePage = TSGeneratedText
    TabOrder = 0
    object TSGeneratedText: TTabSheet
      Caption = 'Generated Text'
      object GBCharacters: TGroupBox
        Left = 3
        Top = 47
        Width = 244
        Height = 286
        TabOrder = 0
        object BvCharSource: TBevel
          Left = 11
          Top = 65
          Width = 218
          Height = 2
          Shape = bsBottomLine
        end
        object TBLetters: TToolBar
          Left = 3
          Top = 7
          Width = 238
          Height = 46
          Align = alNone
          Caption = 'TBLetters'
          TabOrder = 0
        end
        object CBSelectAll: TCheckBox
          Left = 11
          Top = 82
          Width = 77
          Height = 17
          Caption = 'Select all'
          TabOrder = 1
          OnClick = CBSelectAllClick
        end
        object CBNumbers: TCheckBox
          Left = 11
          Top = 105
          Width = 97
          Height = 17
          Caption = 'Numbers'
          TabOrder = 2
        end
        object CBPunctuation: TCheckBox
          Left = 132
          Top = 104
          Width = 97
          Height = 17
          Caption = 'Punctuation'
          TabOrder = 3
        end
        object CBCapitalLetters: TCheckBox
          Left = 132
          Top = 81
          Width = 97
          Height = 17
          Caption = 'Capital letters'
          TabOrder = 4
        end
      end
      object GBWords: TGroupBox
        Left = 253
        Top = 47
        Width = 244
        Height = 286
        TabOrder = 1
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
          OnChange = LVWordsChange
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
          TabOrder = 6
        end
        object BtAddSave: TButton
          Left = 180
          Top = 256
          Width = 57
          Height = 23
          Caption = 'Save'
          TabOrder = 7
          OnClick = BtAddSaveClick
        end
        object BtDelete: TButton
          Left = 104
          Top = 256
          Width = 56
          Height = 23
          Caption = 'Delete'
          TabOrder = 8
          OnClick = BtDeleteClick
        end
      end
      object RGGeneratedText: TRadioGroup
        Left = 3
        Top = 0
        Width = 495
        Height = 41
        Columns = 2
        Items.Strings = (
          'Characters'
          'Words')
        TabOrder = 2
        OnClick = RGGeneratedTextClick
      end
    end
    object TSExternalSources: TTabSheet
      Caption = 'External Sources'
      ImageIndex = 2
      object TreeView1: TTreeView
        Left = 3
        Top = 3
        Width = 205
        Height = 337
        Indent = 19
        TabOrder = 0
      end
    end
    object TSCustomText: TTabSheet
      Caption = 'Custom Text'
      ImageIndex = 1
    end
  end
  object BtCancel: TButton
    Left = 442
    Top = 394
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object BtAccept: TButton
    Left = 350
    Top = 394
    Width = 75
    Height = 25
    Caption = 'Accept'
    ModalResult = 1
    TabOrder = 2
    OnClick = BtAcceptClick
  end
  object DFileOpen: TOpenTextFileDialog
    DefaultExt = 'txt'
    Filter = 'Text Files (*.txt)|*.txt'
    Title = 'Find file'
    Left = 462
    Top = 149
  end
end
