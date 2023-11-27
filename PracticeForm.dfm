object FPractice: TFPractice
  Left = 0
  Top = 0
  Caption = 'Select a text source'
  ClientHeight = 425
  ClientWidth = 537
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
    Width = 525
    Height = 373
    ActivePage = TSGeneratedText
    TabOrder = 0
    object TSGeneratedText: TTabSheet
      Caption = 'Generated Text'
      object GBCharacters: TGroupBox
        Left = 3
        Top = 47
        Width = 250
        Height = 286
        TabOrder = 0
        object BvCharSource: TBevel
          Left = 11
          Top = 98
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
          Top = 111
          Width = 77
          Height = 17
          Caption = 'Select all'
          TabOrder = 1
          OnClick = CBSelectAllClick
        end
        object CBNumbers: TCheckBox
          Left = 11
          Top = 137
          Width = 97
          Height = 17
          Caption = 'Numbers'
          TabOrder = 2
        end
        object CBPunctuation: TCheckBox
          Left = 138
          Top = 137
          Width = 97
          Height = 17
          Caption = 'Punctuation'
          TabOrder = 3
        end
        object CBCapitalLetters: TCheckBox
          Left = 138
          Top = 114
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
          Style = csDropDownList
          TabOrder = 6
        end
        object BtAddSave1: TButton
          Left = 180
          Top = 256
          Width = 57
          Height = 23
          Caption = 'Save'
          TabOrder = 7
          OnClick = BtAddSave1Click
        end
        object BtDelete1: TButton
          Left = 104
          Top = 256
          Width = 56
          Height = 23
          Caption = 'Delete'
          TabOrder = 8
          OnClick = BtDelete1Click
        end
      end
      object RGGeneratedText: TRadioGroup
        Left = 3
        Top = 0
        Width = 511
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
      object LParagraph: TLabel
        Left = 163
        Top = 260
        Width = 57
        Height = 15
        Caption = 'Paragraph:'
      end
      object LAuthor: TLabel
        Left = 163
        Top = 207
        Width = 40
        Height = 15
        Caption = 'Author:'
      end
      object LTitle: TLabel
        Left = 283
        Top = 207
        Width = 25
        Height = 15
        Caption = 'Title:'
      end
      object LYear: TLabel
        Left = 403
        Top = 207
        Width = 25
        Height = 15
        Caption = 'Year:'
      end
      object TVLiteratureCategories: TTreeView
        Left = 3
        Top = 3
        Width = 148
        Height = 337
        Indent = 19
        TabOrder = 0
        OnChange = TVLiteratureCategoriesChange
        Items.NodeData = {
          0301000000280000000000000000000000FFFFFFFFFFFFFFFF00000000000000
          0002000000010542006F006F006B0073002C0000000000000000000000FFFFFF
          FFFFFFFFFF0000000000000000030000000107460069006300740069006F006E
          00280000000000000000000000FFFFFFFFFFFFFFFF0000000000000000000000
          0001054400720061006D0061002C0000000000000000000000FFFFFFFFFFFFFF
          FF000000000000000000000000010743006C00610073007300690063002C0000
          000000000000000000FFFFFFFFFFFFFFFF000000000000000000000000010746
          0061006E007400610073007900340000000000000000000000FFFFFFFFFFFFFF
          FF000000000000000002000000010B4E006F006E002D00460069006300740069
          006F006E002C0000000000000000000000FFFFFFFFFFFFFFFF00000000000000
          0000000000010753006300690065006E00630065003200000000000000000000
          00FFFFFFFFFFFFFFFF000000000000000000000000010A5000680069006C006F
          0073006F00700068007900}
      end
      object LVLiteratureDetails: TListView
        Left = 163
        Top = 3
        Width = 351
        Height = 94
        Columns = <
          item
            Caption = 'Author'
            Width = 110
          end
          item
            Caption = 'Title'
            Width = 180
          end
          item
            Caption = 'Year'
            Width = 55
          end>
        TabOrder = 1
        ViewStyle = vsReport
      end
      object MParagraph: TMemo
        Left = 163
        Top = 109
        Width = 351
        Height = 84
        Lines.Strings = (
          '')
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 2
      end
      object EAuthor: TEdit
        Left = 163
        Top = 228
        Width = 108
        Height = 23
        TabOrder = 3
      end
      object ETitle: TEdit
        Left = 283
        Top = 228
        Width = 111
        Height = 23
        TabOrder = 4
      end
      object EYear: TEdit
        Left = 406
        Top = 228
        Width = 108
        Height = 23
        TabOrder = 5
      end
      object BtAddSave2: TButton
        Left = 456
        Top = 317
        Width = 58
        Height = 23
        Caption = 'Edit'
        TabOrder = 6
      end
      object BtDelete2: TButton
        Left = 387
        Top = 317
        Width = 58
        Height = 23
        Caption = 'Delete'
        TabOrder = 7
      end
      object EParagraph: TEdit
        Left = 163
        Top = 281
        Width = 351
        Height = 23
        TabOrder = 8
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
    Left = 465
    Top = 152
  end
  object XMLDocument1: TXMLDocument
    Active = True
    FileName = 
      'C:\Users\surf3r\OneDrive\Documents\Embarcadero\Studio\Projects\K' +
      'eyType\Data\books.xml'
    Options = [doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    Left = 312
    Top = 220
  end
  object XMLTransform1: TXMLTransform
    Left = 249
    Top = 219
  end
end
